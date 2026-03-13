%% ===== Simulink Result Plot Script =====
% 사용 전제:
% 1) 시뮬레이션 결과가 out 구조체에 저장됨
% 2) 로그 이름:
%    out.temp_log
%    out.pwm_log
%    out.fault_log
%    out.u_raw_log
%    out.I_term_log
%
% 사용 방법:
% - 시뮬레이션 실행 후
% - 아래 set_temp_val, graph_type 수정
% - 스크립트 실행

clearvars -except out
close all
clc

%% ===== 사용자 설정 =====
graph_type   = 'pi';   % 'plant', 'p', 'pi', 'antiwindup', 'fault'
set_temp_val = 45;        % 현재 시뮬레이션에서 사용한 setpoint 값
save_figure  = true;     % 저장하려면 true
save_name    = ['plot_' graph_type '.png'];

%% ===== 데이터 추출 =====
t    = out.temp_log.time(:);
temp = out.temp_log.signals.values(:,1);

% pwm/fault/u_raw/I_term이 없는 경우도 있을 수 있으니 방어적으로 처리
has_pwm   = isprop(out, 'pwm_log')   || isfield(out, 'pwm_log');
has_fault = isprop(out, 'fault_log') || isfield(out, 'fault_log');
has_uraw  = isprop(out, 'u_raw_log') || isfield(out, 'u_raw_log');
has_iterm = isprop(out, 'I_term_log') || isfield(out, 'I_term_log');

if has_pwm
    pwm = out.pwm_log.signals.values(:,1);
else
    pwm = [];
end

if has_fault
    fault = out.fault_log.signals.values(:,1);
else
    fault = [];
end

if has_uraw
    u_raw = out.u_raw_log.signals.values(:,1);
else
    u_raw = [];
end

if has_iterm
    I_term = out.I_term_log.signals.values(:,1);
else
    I_term = [];
end

set_temp_vector = ones(size(t)) * set_temp_val;

%% ===== 그래프 생성 =====
switch lower(graph_type)

    case 'plant'
        % Open-loop Plant Response
        figure('Color','w');
        plot(t, temp, 'b', 'LineWidth', 2); hold on
        grid on
        xlabel('Time (s)')
        ylabel('Temperature')
        title('Open-loop Plant Response')
        legend('temp', 'Location', 'best')

    case 'p'
        % P Control Response
        figure('Color','w');
        h1 = plot(t, temp, 'b', 'LineWidth', 2); hold on
        h2 = plot(t, set_temp_vector, 'k--', 'LineWidth', 2);
        h3 = plot(t, pwm, 'r', 'LineWidth', 2);
        grid on
        xlabel('Time (s)')
        ylabel('Value')
        title('P Controller Response')
        legend([h1(1), h2(1), h3(1)], {'temp', 'set\_temp', 'pwm'}, 'Location', 'best')

    case 'pi'
        % PI Control Response
        figure('Color','w');
        h1 = plot(t, temp, 'b', 'LineWidth', 2); hold on
        h2 = plot(t, set_temp_vector, 'k--', 'LineWidth', 2);
        h3 = plot(t, pwm, 'r', 'LineWidth', 2);
        grid on
        xlabel('Time (s)')
        ylabel('Value')
        title('PI Controller Response')
        legend([h1(1), h2(1), h3(1)], {'temp', 'set\_temp', 'pwm'}, 'Location', 'best')

    case 'antiwindup'
        % Anti-windup Demonstration
        figure('Color','w');
        h1 = plot(t, u_raw, 'm', 'LineWidth', 2); hold on
        h2 = plot(t, pwm, 'r', 'LineWidth', 2);
        h3 = plot(t, I_Term, 'g', 'LineWidth', 2);
        grid on
        xlabel('Time (s)')
        ylabel('Value')
        title('Anti-windup Behavior')
        legend([h1(1), h2(1), h3(1)], {'u\_raw', 'pwm', 'I\_term'}, 'Location', 'best')

    case 'fault'
        % Fault / Fail-safe Response
        figure('Color','w');

        yyaxis left
        h1 = plot(t, temp, 'b', 'LineWidth', 2); hold on
        h2 = plot(t, set_temp_vector, 'k--', 'LineWidth', 2);
        h3 = plot(t, pwm, 'r', 'LineWidth', 2);
        ylabel('Temperature / PWM')

        yyaxis right
        h4 = plot(t, fault, 'g', 'LineWidth', 2);
        ylabel('Fault Flag')
        ylim([0 1.2])

        grid on
        xlabel('Time (s)')
        title('Fault and Fail-safe Response')
        legend([h1(1), h2(1), h3(1), h4(1)], {'temp', 'set\_temp', 'pwm', 'fault'}, 'Location', 'best')

    otherwise
        error('graph_type must be one of: plant, p, pi, antiwindup, fault');
end

%% ===== 그림 저장 =====
if save_figure
    exportgraphics(gcf, save_name, 'Resolution', 300);
    fprintf('Figure saved: %s\n', save_name);
end