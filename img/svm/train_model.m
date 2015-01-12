function model = train_model(train_labels, train_data)

model = lintrain(train_labels, sparse(train_data), '-s 0 -c 1e6  -p 0.1');

end
