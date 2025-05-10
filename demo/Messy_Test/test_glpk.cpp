#ifdef _MSC_VER
#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <string>
#include "glpk.h"

// Blog: https://blog.csdn.net/fengbingchun/article/details/147855898

int test_glpk()
{
	constexpr int total_foods{ 9 };
	const std::vector<std::string> foods{ "food1", "food2", "food3", "food4", "food5", "food6", "food7", "food8", "food9" };
	const std::vector<float> unit_prices{ 0.886, 0.863, 0.855, 0.917, 0.237, 0.856, 0.833, 0.904, 0.876 };
	const std::vector<std::array<float, 2>> bounds{ {1.0, 55.0}, {1.0, 55.0}, {1.0, 55.0}, {1.0, 55.0}, {7.0, 9.0}, {1.0, 55.0}, {1.0, 55.0}, {1.0, 55.0}, {1.0, 55.0} };

	constexpr int num_nutrients{ 4 };
	const std::vector<std::string> nutrients{ "nutrient1", "nutrient2", "nutrient3", "nutrient4" };
	const std::vector<std::array<float, 4>> nutrient_values{ {0.21, 65.10, 0.72, 88.5}, {0.08, 64.58, 0.63, 76.9}, {0.22, 64.81, 0.53, 86.1}, {0.58, 65.84, 1.09, 57.8}, {0.033, 46.07, 14.15, 0},
																{0.059, 65.25, 0.39, 87.2}, {0.14, 64.25, 0.57, 93.7}, {0.033, 63.06, 1.36, 79.0}, {0.076, 65.20, 0.59, 99.0} };
	const std::vector<std::array<float, 2>> nutrient_limit{ {0., 49.}, {6200., 6230.}, {9.9, 782.}, {6500., 7000.} };

	constexpr float total_quantity{ 99. };
	const std::string mandatory_food{ "food5" };
	constexpr int num_select_foods{ 5 };

	if (foods.size() != total_foods) {
		std::cerr << "Error: number of foods mismatch" << std::endl;
		return -1;
	}
	if (unit_prices.size() != total_foods) {
		std::cerr << "Error: number of unit_prices mismatch" << std::endl;
		return -1;
	}
	if (bounds.size() != total_foods) {
		std::cerr << "Error: number of bounds mismatch" << std::endl;
		return -1;
	}
	if (nutrient_values.size() != total_foods) {
		std::cerr << "Error: number of nutrient_values mismatch" << std::endl;
		return -1;
	}

	if (nutrients.size() != num_nutrients) {
		std::cerr << "Error: number of nutrients mismatch" << std::endl;
		return -1;
	}
	if (nutrient_limit.size() != num_nutrients) {
		std::cerr << "Error: number of nutrient_limit mismatch" << std::endl;
		return -1;
	}

	int mandatroy_food_index{ 0 };
	for (auto i = 0; i < total_foods; ++i) {
		if (mandatory_food == foods[i]) {
			mandatroy_food_index = i;
			break;
		}
	}

	auto lp = glp_create_prob(); // create problem object
	glp_set_prob_name(lp, "diet problem");
	glp_set_obj_dir(lp, GLP_MIN); // minimize objective function

	// add col variables
	glp_add_cols(lp, 2 * total_foods); // first total_foods: number of each food; last total_foods: binary variables, whether the food is selected

	for (auto j = 0; j < total_foods; ++j) {
		// set food number variable
		glp_set_col_name(lp, j + 1, foods[j].c_str());
		glp_set_col_kind(lp, j + 1, GLP_CV); // GLP_IV: number of foods can only be an integer, use MIP; default is GLP_CV
		glp_set_col_bnds(lp, j + 1, GLP_LO, 0.0, 0.0);
		glp_set_obj_coef(lp, j + 1, unit_prices[j]); // set cost coefficient

		// set binary select variables
		std::string name = "S_" + foods[j];
		glp_set_col_name(lp, total_foods + j + 1, name.c_str());
		glp_set_col_kind(lp, total_foods + j + 1, GLP_BV);
		glp_set_obj_coef(lp, total_foods + j + 1, 0.);
	}

	// add row constraints
	glp_add_rows(lp, num_nutrients);

	for (auto i = 0; i < num_nutrients; ++i) {
		glp_set_row_name(lp, i + 1, nutrients[i].c_str());
		glp_set_row_bnds(lp, i + 1, GLP_DB, nutrient_limit[i][0], nutrient_limit[i][1]);
	}

	// add select constraints
	glp_add_rows(lp, 2);
	glp_set_row_name(lp, num_nutrients + 1, "select_total");
	glp_set_row_bnds(lp, num_nutrients + 1, GLP_FX, num_select_foods, num_select_foods);

	// add mandatory food constraint
	glp_set_row_name(lp, num_nutrients + 2, "must_have_food");
	glp_set_row_bnds(lp, num_nutrients + 2, GLP_FX, 1., 1.);

	// add total_quantity constraint
	glp_add_rows(lp, 1);
	glp_set_row_name(lp, num_nutrients + 3, "total_quantity");
	glp_set_row_bnds(lp, num_nutrients + 3, GLP_FX, total_quantity, total_quantity);

	// constraint matrix:
	// glp_load_matrix(lp, ne, ia, ja, ar): for k = 1,..., ne, where ia[k] is the row index, ja[k] is the column index, and ar[k] is a numeric value of corresponding constraint coefficient
	// parameter ne specifies the total number of (non-zero) elements in the matrix to be loaded
	int ia[1 + 1000]{}, ja[1 + 1000]{}, k{ 0 };
	double ar[1 + 1000]{};

	// nutrients constraint
	for (auto i = 0; i < num_nutrients; ++i) {
		for (auto j = 0; j < total_foods; ++j) {
			k++;
			ia[k] = i + 1, ja[k] = j + 1;
			ar[k] = nutrient_values[j][i];
		}
	}

	// select total constraint
	for (auto j = 0; j < total_foods; ++j) {
		k++;
		ia[k] = num_nutrients + 1, ja[k] = total_foods + j + 1;
		ar[k] = 1.;
	}

	// mandatory food constraint
	k++;
	ia[k] = num_nutrients + 2, ja[k] = total_foods + mandatroy_food_index + 1;
	ar[k] = 1.;

	// total_quantity constraint
	for (auto j = 0; j < total_foods; ++j) {
		k++;
		ia[k] = num_nutrients + 3, ja[k] = j + 1;
		ar[k] = 1.;
	}

	// add relationship constraint between food quantity and select variable
	for (auto j = 0; j < total_foods; ++j) {
		// lower constraint: quantity_j >= min_j * select_j
		glp_add_rows(lp, 1);
		glp_set_row_name(lp, num_nutrients + 4 + 2 * j, "quantity_min");
		glp_set_row_bnds(lp, num_nutrients + 4 + 2 * j, GLP_LO, 0., 0.);
		
		// quantity_j coefficient: 1.0
		k++;
		ia[k] = num_nutrients + 4 + 2 * j, ja[k] = j + 1;
		ar[k] = 1.;

		// select_j cofficient: -min_j
		k++;
		ia[k] = num_nutrients + 4 + 2 * j, ja[k] = total_foods + j + 1;
		ar[k] = -bounds[j][0];

		// upper constraint: quantity_j <= max_j * select_j
		glp_add_rows(lp, 1);
		glp_set_row_name(lp, num_nutrients + 4 + 2 * j + 1, "quantity_max");
		glp_set_row_bnds(lp, num_nutrients + 4 + 2 * j + 1, GLP_UP, 0., 0.);

		k++;
		ia[k] = num_nutrients + 4 + 2 * j + 1, ja[k] = j + 1;
		ar[k] = 1.;

		k++;
		ia[k] = num_nutrients + 4 + 2 * j + 1, ja[k] = total_foods + j + 1;
		ar[k] = -bounds[j][1];
	}

	glp_load_matrix(lp, k, ia, ja, ar);

	// verify constraint matrix and variables
	std::cout << "number of constraints: " << glp_get_num_rows(lp) << std::endl;
	for (auto i = 1; i <= glp_get_num_rows(lp); ++i)
		std::cout << "i: " << i << "; type: " << glp_get_row_type(lp, i) << "; lower: " << glp_get_row_lb(lp, i) << "; upper: " << glp_get_row_ub(lp, i) << std::endl;

	std::cout << "number of variables: " << glp_get_num_cols(lp) << std::endl;
	for (auto j = 1; j <= glp_get_num_cols(lp); ++j) // Note: the value of glp_get_col_prim is different in different positions
		std::cout << "j: " << j << "; kind: " << glp_get_col_kind(lp, j) << "; primal value: " << glp_get_col_prim(lp, j) << "; lower: " << glp_get_col_lb(lp, j) << "; upper: " << glp_get_col_ub(lp, j) << "; coef: " << glp_get_obj_coef(lp, j) << std::endl;

	auto ret = glp_write_lp(lp, nullptr, "../../../testdata/model.lp");
	if (ret != 0) {
		std::cerr << "Error: failed to write problem data, error code: " << ret << std::endl;
		glp_delete_prob(lp);
		return -1;
	}

	double quantity_sum{ 0. };
	if (0) { // LP(Linear Programming)
		glp_smcp parm{};
		glp_init_smcp(&parm);
		parm.msg_lev = GLP_MSG_ERR; // warning and error messages only
		parm.presolve = GLP_ON;
		ret = glp_simplex(lp, &parm); // solve LP problem with the primal or dual simplex method
		if (ret != 0) {
			std::cerr << "Error: failed to solve: error code: " << ret << std::endl;
			glp_delete_prob(lp);
			return -1;
		}

		ret = glp_get_status(lp);
		if (ret != GLP_OPT) {
			std::cerr << "Error: there is no optimal solution, status: " << ret << std::endl;
			glp_delete_prob(lp);
			return -1;
		}

		std::cout << "minimum cost: " << glp_get_obj_val(lp) << std::endl;
		for (auto j = 0; j < total_foods; ++j) {
			auto qty = glp_get_col_prim(lp, j + 1);
			auto selected = glp_get_col_prim(lp, total_foods + j + 1);
			if (selected > 0.5) {
				std::cout << foods[j] << ": quantity: " << qty << ", limit: [" << bounds[j][0] << "," << bounds[j][1] << "]" << std::endl;
				quantity_sum += qty;
			}
		}
	}
	else { // MIP(Mixed Integer linear Programming)
		glp_iocp parm;
		glp_init_iocp(&parm);
		parm.presolve = GLP_ON;
		parm.msg_lev = GLP_MSG_ERR; // close information output prompt
		ret = glp_intopt(lp, &parm);
		if (ret != 0) {
			std::cerr << "Error: failed to solve: error code: " << ret << std::endl;
			glp_delete_prob(lp);
			return -1;
		}

		ret = glp_mip_status(lp);
		if (ret != GLP_OPT) {
			std::cerr << "Error: there is no optimal solution, status: " << ret << std::endl;
			glp_delete_prob(lp);
			return -1;
		}

		std::cout << "minimum cost: " << glp_mip_obj_val(lp) << std::endl;
		for (auto j = 0; j < total_foods; ++j) {
			auto qty = glp_mip_col_val(lp, j + 1);
			auto selected = glp_mip_col_val(lp, total_foods + j + 1);
			if (selected > 0.5) {
				std::cout << foods[j] << ": quantity: " << qty << ", limit: [" << bounds[j][0] << "," << bounds[j][1] << "]" << std::endl;
				quantity_sum += qty;
			}
		}
	}

	std::cout << "result quantity sum: " << quantity_sum << "; require quantity sum: " << total_quantity << std::endl;

	glp_delete_prob(lp);
	return 0;
}


#endif // _MSC_VER

