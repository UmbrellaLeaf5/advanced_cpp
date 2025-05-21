#include "builder.hpp"

int main() {
  // Create some checkpoints
  Checkpoint cp_1("Start", 55.75, 37.62);                       // Mandatory
  Checkpoint cp_2("Forest Crossing", 55.80, 37.70, 0.5, true);  // Optional
  Checkpoint cp_3("River Ford", 55.85, 37.75, 1.0, true);       // Optional
  Checkpoint cp_4("Finish", 55.90, 37.80);                      // Mandatory

  std::vector<Checkpoint> checkpoints = {cp_1, cp_2, cp_3, cp_4};

  // Build the text list
  TextCheckpointListBuilder text_builder;
  RaceTrackDirector director;
  director.Construct(&text_builder, checkpoints);
  std::cout << text_builder.GetResult() << "\n";

  // Calculate the total penalty
  PenaltyCheckpointListBuilder penalty_builder;
  director.Construct(&penalty_builder, checkpoints);
  std::cout << penalty_builder.GetResult() << "\n";

  return 0;
}
