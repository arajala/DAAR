function [labels acc prob] = test_model(test_labels, test_data, model)

[labels, acc, prob] = linpredict(test_labels, sparse(test_data), model);

end
