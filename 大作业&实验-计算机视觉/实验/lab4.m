clc
clear
close all

% ��ȡ����
load('notMNIST_small.mat')

% ѡȡ�������ݿ��ӻ�
for i=1:1:32
    subplot(4,8,i);
    imshow(images(:,:,555*i)/255)
end

% 
X = reshape(images, [28,28,1,length(images)]); % �Ҷ�ͼƬ����Ϊ�����Ҫ��Ϊh*w**c*s,
                                               % ����hΪͼƬ�ĳ��ȣ�wΪ��ȣ�cΪͨ������s�������ݵĸ���
size(X)                                        % ���Կ������ǵ����ݼ��ߴ�Ϊ��28*28*1*18724
Y = categorical(labels);                       % ��ǩ����������Ϊcategorical

idx = randperm(length(images));   % ����һ�������ݸ���һ�µ����������
num_train = round(0.5*length(X)); % ѵ����������0.5��ʾȫ�����������ѡȡ50%��Ϊѵ����
num_val = round(0.3*length(X));   % ��֤��������0.3��ʾȫ�����������ѡȡ30%��Ϊ��֤�����ʲ��Լ��Զ���Ϊʣ�µ�20%

% ѵ��������֤���Ͳ��Լ�����
X_train = X(:,:,:,idx(1:num_train));
X_val = X(:,:,:,idx(num_train+1:num_train+num_val));
X_test = X(:,:,:,idx(num_train+num_val+1:end));  %������裬ȫ�������г���

% ѵ��������֤���Ͳ��Լ���ǩ
Y_train = Y(idx(1:num_train),:);
Y_val = Y(idx(num_train+1:num_train+num_val),:);
Y_test = Y(idx(num_train+num_val+1:end),:);
%% ���������
layers = [...
          imageInputLayer([28,28,1]); % ����㣬Ҫ��ȷ����ͼƬ��height, width �� number of channels of the images
          batchNormalizationLayer();  % ������һ��
          convolution2dLayer(5,20);   % �����
          batchNormalizationLayer();
          reluLayer()                 % Relu����� 
          maxPooling2dLayer(2,'Stride',2); % �ػ���
          fullyConnectedLayer(10);       % ȫ���Ӳ�
          softmaxLayer();                % softmax��
          classificationLayer(),...
    ];
% ����
options = trainingOptions('sgdm',...   % Ҳ������adam��rmsprop�ȷ���
    'MaxEpochs',50,...                 % ����������
    'Plots','training-progress');
net_cnn = trainNetwork(X_train,Y_train,layers,options);
% ����
options = trainingOptions('sgdm',...                         % Ҳ������adam��rmsprop�ȷ���
                          'MiniBatchSize',128, ...
                          'MaxEpochs',50,...                 % ����������
                          'ValidationData',{X_val,Y_val},... % ��ʾ��֤�����
                          'Verbose',true, ...                % �������ʾѵ�����̵ĸ���ָ��
                          'Shuffle','every-epoch', ...
                          'InitialLearnRate',1e-2,...
                          'Plots','training-progress');
net_cnn = trainNetwork(X_train,Y_train,layers,options);
% ����
testLabel = classify(net_cnn,X_test);
precision = sum(testLabel==Y_test)/numel(testLabel);
disp(['���Լ�����׼ȷ��Ϊ',num2str(precision*100),'%'])