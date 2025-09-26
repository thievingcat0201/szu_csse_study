

% 生成瑞士卷数据
n_samples = 1000;
noise_level = 0.1; % 噪声水平
[X, color] = make_swiss_roll(n_samples, noise_level);

% 可视化原始3D瑞士卷数据
figure;
subplot(1, 2, 1);
scatter3(X(:, 1), X(:, 2), X(:, 3), 20, color, 'filled');
colormap parula; % 使用 parula 颜色映射
colorbar; % 添加颜色条
title('Original 3D Swiss Roll with Noise', 'FontSize', 14);
xlabel('X', 'FontSize', 12);
ylabel('Y', 'FontSize', 12);
zlabel('Z', 'FontSize', 12);
grid on;
axis equal; % 设置坐标轴比例一致
view(-30, 15); % 调整视角

% Isomap 参数
k = 10; % 邻域大小
n_components = 2; % 降维到2维

% 构建邻域图
D = pdist2(X, X); % 计算欧氏距离矩阵
A = zeros(size(D)); % 邻接矩阵
for i = 1:size(X, 1)
    [~, idx] = sort(D(i, :)); % 找到每个点的 k 个最近邻
    A(i, idx(2:k+1)) = D(i, idx(2:k+1)); % 构建邻接矩阵
    A(idx(2:k+1), i) = D(idx(2:k+1), i); % 对称邻接矩阵
end

% 计算测地线距离（最短路径）
G = graph(A); % 将邻接矩阵转换为图对象
D_geo = distances(G); % 计算所有点对之间的最短路径

% 多维缩放（MDS）
D_geo_centered = D_geo.^2; % 平方距离
J = eye(size(D_geo)) - (1/size(D_geo, 1)) * ones(size(D_geo)); % 中心化矩阵
B = -0.5 * J * D_geo_centered * J; % 中心化距离矩阵
[coeff, latent] = eig(B); % 特征分解
[~, idx] = sort(diag(latent), 'descend'); % 按特征值排序
coeff = coeff(:, idx); % 排序特征向量
X_isomap = coeff(:, 1:n_components) * sqrt(latent(idx(1:n_components), idx(1:n_components))); % 投影到低维空间

% 可视化Isomap降维结果
subplot(1, 2, 2);
scatter(X_isomap(:, 1), X_isomap(:, 2), 20, color, 'filled');
colormap parula; % 使用 parula 颜色映射
colorbar; % 添加颜色条
title('Isomap Projection to 2D with Noise', 'FontSize', 14);
xlabel('Component 1', 'FontSize', 12);
ylabel('Component 2', 'FontSize', 12);
grid on;


% 自定义瑞士卷生成函数
function [X, color] = make_swiss_roll(n_samples, noise_level)
    % 生成瑞士卷数据
    t = 3 * pi / 2 * (1 + 2 * rand(1, n_samples));
    height = 21 * rand(1, n_samples);
    X = [t .* cos(t); height; t .* sin(t)]';
    
    % 添加噪声
    X = X + noise_level * randn(size(X)); % 添加高斯噪声
    
    % 颜色表示数据点在流形上的位置
    color = t; % 使用 t 作为颜色值
end