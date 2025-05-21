#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Checkpoint;

// Builder interface
class CheckpointListBuilder {
 public:
  virtual void Reset() = 0;
  virtual void Add(const Checkpoint& checkpoint) = 0;
  virtual std::string GetResult() = 0;  // Changed return type to std::string
  virtual ~CheckpointListBuilder() {}   // Virtual destructor
};

// Product: Checkpoint
class Checkpoint {
 public:
  std::string name;
  double latitude;
  double longitude;
  double penalty;  // Penalty for optional checkpoints, 0 for mandatory
  bool is_optional;

  Checkpoint(const std::string& name, double latitude, double longitude,
             double penalty, bool is_optional)
      : name(name),
        latitude(latitude),
        longitude(longitude),
        penalty(penalty),
        is_optional(is_optional) {}

  Checkpoint(const std::string& name, double latitude, double longitude)
      : Checkpoint(name, latitude, longitude, 0.0, false) {}
};

// Concrete Builder 1: Text Output
class TextCheckpointListBuilder : public CheckpointListBuilder {
 private:
  std::string result_;
  int checkpoint_count_;

 public:
  TextCheckpointListBuilder() : checkpoint_count_(0) { Reset(); }

  void Reset() override {
    result_ = "";
    checkpoint_count_ = 0;
  }

  void Add(const Checkpoint& checkpoint) override {
    checkpoint_count_++;

    result_ += std::to_string(checkpoint_count_) + ". ";
    result_ += checkpoint.name + "; ";
    result_ += "Latitude: " + std::to_string(checkpoint.latitude) +
               ", Longitude: " + std::to_string(checkpoint.longitude) + "; ";

    result_ +=
        checkpoint.is_optional
            ? "Penalty: " + std::to_string(checkpoint.penalty) + " hours\n"
            : "Penalty: Failure\n";
  }

  std::string GetResult() override { return result_; }
};

// Concrete Builder 2: Total Penalty Calculation
class PenaltyCheckpointListBuilder : public CheckpointListBuilder {
 private:
  double total_penalty_;

 public:
  PenaltyCheckpointListBuilder() { Reset(); }

  void Reset() override { total_penalty_ = 0.0; }

  void Add(const Checkpoint& checkpoint) override {
    if (checkpoint.is_optional) total_penalty_ += checkpoint.penalty;
  }

  std::string GetResult() override {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << total_penalty_;
    return "Total Penalty: " + ss.str() + " hours";
  }
};

class RaceTrackDirector {
 public:
  void Construct(CheckpointListBuilder* builder,
                 const std::vector<Checkpoint>& checkpoints) {
    builder->Reset();

    for (const auto& checkpoint : checkpoints) builder->Add(checkpoint);
  }
};
