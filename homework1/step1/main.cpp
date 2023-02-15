#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("tor");

  double lc = 0.03;
  double pi = 3.14159;
  double r = 0.3;//ìàëåíüêèé ðàäèóñ 1
  double R = 0.6;//áîëüøîé ðàäèóñ
  double t = 0.2; //ìàëåíüêèé ðàäèóñ 2

  gmsh::model::occ::addPoint( R,  0,  0, lc, 1);

  //òî÷êè áîëüøåãî êðóãà
  gmsh::model::occ::addPoint( r + R,  0,  0, lc, 2);
  gmsh::model::occ::addPoint( R , r ,  0, lc, 3);
  gmsh::model::occ::addPoint( R - r,  0,  0, lc, 4);
  gmsh::model::occ::addPoint(  R , -r ,  0, lc, 5);

  //òî÷êè ìåíüøåãî êðóãà
  gmsh::model::occ::addPoint( t + R,  0,  0, lc, 12);
  gmsh::model::occ::addPoint( R , t ,  0, lc, 13);
  gmsh::model::occ::addPoint( R - t,  0,  0, lc, 14);
  gmsh::model::occ::addPoint(  R , -t ,  0, lc, 15);

  gmsh::model::occ::addCircleArc(2, 1, 3, 1);
  gmsh::model::occ::addCircleArc(3, 1, 4, 2);
  gmsh::model::occ::addCircleArc(4, 1, 5, 3);
  gmsh::model::occ::addCircleArc(5, 1, 2, 4);

  gmsh::model::occ::addCircleArc(12, 1, 13, 11);
  gmsh::model::occ::addCircleArc(13, 1, 14, 12);
  gmsh::model::occ::addCircleArc(14, 1, 15, 13);
  gmsh::model::occ::addCircleArc(15, 1, 12, 14);

  gmsh::model::occ::addCurveLoop({1, 2, 3, 4}, 1);
  gmsh::model::occ::addPlaneSurface({1}, 1);

  gmsh::model::occ::addCurveLoop({11, 12, 13, 14}, 2);
  gmsh::model::occ::addPlaneSurface({2}, 2);

  std::vector<std::pair<int, int> > ov;
  std::vector<std::vector<std::pair<int, int> > > ovv;
  gmsh::model::occ::cut({{2, 1}}, {{2, 2}}, ov, ovv, 3);

  std::vector<std::pair<int, int> > v1, v2;

  gmsh::model::occ::revolve({{2, 3}}, 0, 0.1, 0, 0, 0.1, 0, pi - 0.00001, v1);
  gmsh::model::occ::revolve({{2, 3}}, 0, 0.1, 0, 0, -0.1, 0, pi - 0.00001, v2);



  gmsh::model::occ::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("tor.msh");

  gmsh::finalize();

  return 0;
}

