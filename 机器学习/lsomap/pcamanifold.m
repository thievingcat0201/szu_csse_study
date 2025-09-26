% 生成瑞士卷数据
n_samples = 1000;
noise = 0.1;
[X, color] = make_swiss_roll(n_samples, noise);

% 可视化原始3D瑞士卷数据
figure;
subplot(1, 2, 1);
scatter3(X(:, 1), X(:, 2), X(:, 3), 40, color, 'filled');
title('3D 瑞士卷');
xlabel('X');
ylabel('Y');
zlabel('Z');
grid on;

% pca
X_centered = X - mean(X); % 数据中心化
cov_matrix = (X_centered' * X_centered) / (size(X, 1) - 1); % 计算协方差矩阵
[coeff, latent] = eig(cov_matrix); % 特征分解
[~, idx] = sort(diag(latent), 'descend'); % 按特征值从大到小排序
coeff = coeff(:, idx); % 排序特征向量
X_pca = X_centered * coeff(:, 1:2); % 投影到前两个主成分

% 可视化PCA降维结果
subplot(1, 2, 2);
scatter(X_pca(:, 1), X_pca(:, 2), 40, color, 'filled');
title('PCA 投影到 2D');
xlabel('PC1');
ylabel('PC2');
grid on;

% 自定义瑞士卷生成函数
function [X, color] = make_swiss_roll(n_samples, noise)
    % 生成瑞士卷数据
    t = 3 * pi / 2 * (1 + 2 * rand(1, n_samples));
    height = 21 * rand(1, n_samples);
    X = [t .* cos(t); height; t .* sin(t)]';
    
    % 添加噪声
    X = X + noise * randn(size(X));
    
    % 颜色表示数据点在流形上的位置
    color = t; % 使用 t 作为颜色值
end