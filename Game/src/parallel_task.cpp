// Copyright 2015, Aaron Ceross

#include "parallel_task.cpp"

ParallelTask::ParallelTask()
: thread_(&ParallelTask::RunTask, this), finished_(false)
{}

void ParallelTask::Execute() {
  finished_ = false;
  elapsed_time_.restart();
  thread_.launch();
}

bool ParallelTask::IsFinished() {
  sf::Lock lock(mutex_);
  return finished_;
}

float ParallelTask::getCompletion() {
  sf::Lock lock(mutex_);

  // 100% at 10 seconds of elapsed time
  return elapsed_time_.getElapsedTime().asSeconds() / 10.f;
}

void ParallelTask::RunTask() {
  // Dummy task - stall 10 seconds
  bool ended = false;
  while (!ended) {
    sf::Lock lock(mutex_);  // Protect the clock
    if (elapsed_time_.getElapsedTime().asSeconds() >= 10.f)
      ended = true;
  }

  { // mFinished may be accessed from multiple threads, protect it
    sf::Lock lock(mutex_);
    finished_ = true;
  }
}
