/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2020 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file simplex/HEkkPrimal.h
 * @brief Phase 2 primal simplex solver for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef SIMPLEX_HEKKPRIMAL_H_
#define SIMPLEX_HEKKPRIMAL_H_

//#include <utility>

//#include "HConfig.h"
#include "lp_data/HighsStatus.h"
//#include "simplex/SimplexConst.h"
#include "simplex/HEkk.h"
//#include "simplex/HVector.h"

using std::pair;

const SimplexAlgorithm algorithm = SimplexAlgorithm::PRIMAL;
const bool use_bound_perturbation = false;

/**
 * @brief Primal simplex solver for HiGHS
 *
 */

class HEkkPrimal {
 public:
  HEkkPrimal(HEkk& simplex) : ekk_instance_(simplex) { initialise(); }

  // References:
  //
  // Simplex instance
  HEkk& ekk_instance_;
  /**
   * @brief Solve a model instance
   */
  HighsStatus solve();

 private:
  void initialise();
  void solvePhase2();

  void primalRebuild();
  void primalChooseColumn();
  void primalChooseRow();
  void primalUpdate();
  //
  void phase1ComputeDual();
  void phase1ChooseColumn();
  void phase1ChooseRow();
  void phase1Update();
  //
  void devexReset();
  void devexUpdate();
  //
  void iterationAnalysisData();
  //
  void iterationAnalysis();
  //
  void reportRebuild(const int rebuild_invert_hint = -1);
  //
  HighsSimplexAnalysis* analysis;
  int num_col;
  int num_row;
  int num_tot;
  //
  bool no_free_columns;
  //
  int isPrimalPhase1;
  //
  int solvePhase;
  double primal_feasibility_tolerance;
  double dual_feasibility_tolerance;
  //  Pivot related
  int invertHint = INVERT_HINT_NO;
  int columnIn;
  int rowOut;
  int columnOut;
  int phase1OutBnd;
  double thetaDual;
  double thetaPrimal;
  double alpha;
  double alphaRow;
  double numericalTrouble;
  int num_flip_since_rebuild;
  //
  //  Primal phase 1 tools
  vector<pair<double, int> > ph1SorterR;
  vector<pair<double, int> > ph1SorterT;
  //
  //  Devex weight
  int num_devex_iterations;
  int num_bad_devex_weight;
  vector<double> devex_weight;
  vector<int> devex_index;
  //
  //   Solve buffer
  HVector row_ep;
  HVector row_ap;
  HVector col_aq;
};

#endif /* SIMPLEX_HEKKPRIMAL_H_ */