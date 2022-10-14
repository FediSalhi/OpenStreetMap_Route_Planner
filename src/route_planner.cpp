#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  current_node->FindNeighbors();
  for (auto item : current_node->neighbors) {
    if (item->visited == false) {
      item->parent = current_node;
      item->h_value = CalculateHValue(item);
      item->g_value = current_node->g_value + item->distance(*current_node);
      item->visited = true;
      open_list.emplace_back(item);
    }
  }
}

RouteModel::Node *RoutePlanner::NextNode() {

  std::sort(std::begin(open_list), std::end(open_list),
            [](const RouteModel::Node *n1, const RouteModel::Node *n2) {
              return (((float)n1->g_value + (float)n1->h_value) <=
                      ((float)n2->g_value + (float)n2->h_value));
            });

  RouteModel::Node *smallest_f = open_list[0];
  open_list.erase(open_list.begin());
  return smallest_f;
}

std::vector<RouteModel::Node>
RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  while (current_node->parent) {
    // path_found.insert(std::begin(path_found), *current_node);
    // std::vector::insert --> O(N+M)
    path_found.emplace_back(*current_node); // std::vector::emplace_back -->
                                            // O(1) without re-allocation
    distance += current_node->distance(*(current_node->parent));
    current_node = current_node->parent;
  }
  // path_found.insert(std::begin(path_found), *current_node); for the start
  // node, O(N+M)
  path_found.emplace_back(*current_node); // O(1)

  std::reverse(path_found.begin(), path_found.end()); // O(N/2)

  distance *= m_Model.MetricScale(); // Multiply the distance by the scale of
                                     // the map to get meters.
  return path_found;
}

void RoutePlanner::AStarSearch() {

  RouteModel::Node *current_node = nullptr;
  open_list.emplace_back(start_node);
  start_node->visited = true;

  while (open_list.size() > 0) {
    current_node = NextNode();
    if (current_node == end_node) {
      m_Model.path = ConstructFinalPath(end_node);
      break;
    }
    AddNeighbors(current_node);
  }
}