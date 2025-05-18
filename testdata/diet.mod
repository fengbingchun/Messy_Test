# sets
set Foods := {'food1', 'food2', 'food3', 'food4', 'food5', 'food6', 'food7', 'food8', 'food9'};
set Nutrients := {'nutrient1', 'nutrient2', 'nutrient3', 'nutrient4'};

# parameters
param unit_prices{Foods};
param nutrient_values{Foods, Nutrients};
param min_bounds{Foods};
param max_bounds{Foods};
param min_nutrient{Nutrients};
param max_untrient{Nutrients};

# variable
var quantity{Foods} >= 0;
var select{Foods} binary;

# objective function
minimize total_cost: sum{f in Foods} unit_prices[f] * quantity[f];

# constraint
s.t. quantity_min{f in Foods}: quantity[f] >= min_bounds[f] * select[f];
s.t. quantity_max{f in Foods}: quantity[f] <= max_bounds[f] * select[f];

s.t. nutrient_min{n in Nutrients}: sum{f in Foods} nutrient_values[f, n] * quantity[f] >= min_nutrient[n];
s.t. nutrient_max{n in Nutrients}: sum{f in Foods} nutrient_values[f, n] * quantity[f] <= max_untrient[n];

s.t. total_quantity: sum{f in Foods} quantity[f] = 99.0;

s.t. mandatory_food: select['food5'] = 1;

s.t. num_select_foods: sum{f in Foods} select[f] = 5;

solve;

printf "total cost: %.4f\n", total_cost;
printf {f in Foods: select[f] > 0.5}: "selected: %s: %.4f, limit: [%.1f, %.1f]\n", f, quantity[f], min_bounds[f], max_bounds[f];
printf "total quantity: %.1f\n", sum{f in Foods} quantity[f];

# data
data;

param unit_prices :=
    'food1' 0.886
    'food2' 0.863
    'food3' 0.855
    'food4' 0.917
    'food5' 0.237
    'food6' 0.856
    'food7' 0.833
    'food8' 0.904
    'food9' 0.876;

param nutrient_values : 'nutrient1' 'nutrient2' 'nutrient3' 'nutrient4' :=
    'food1' 0.21 65.10 0.72 88.5
    'food2' 0.08 64.58 0.63 76.9
    'food3' 0.22 64.81 0.53 86.1
    'food4' 0.58 65.84 1.09 57.8
    'food5' 0.033 46.07 14.15 0
    'food6' 0.059 65.25 0.39 87.2
    'food7' 0.14 64.25 0.57 93.7
    'food8' 0.033 63.06 1.36 79.0
    'food9' 0.076 65.20 0.59 99.0;

param min_bounds :=
    'food1' 1.0
    'food2' 1.0
    'food3' 1.0
    'food4' 1.0
    'food5' 7.0
    'food6' 1.0
    'food7' 1.0
    'food8' 1.0
    'food9' 1.0;

param max_bounds :=
    'food1' 55.0
    'food2' 55.0
    'food3' 55.0
    'food4' 55.0
    'food5' 9.0
    'food6' 55.0
    'food7' 55.0
    'food8' 55.0
    'food9' 55.0;

param min_nutrient :=
    'nutrient1' 0.
    'nutrient2' 6200.
    'nutrient3' 9.9
    'nutrient4' 6500.;

param max_untrient :=
    'nutrient1' 49.
    'nutrient2' 6230.
    'nutrient3' 782.
    'nutrient4' 7000.;

end;
