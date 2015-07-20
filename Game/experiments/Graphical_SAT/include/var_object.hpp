// Copyright 2015, Aaron Ceross

#ifndef VAR_OBJECT_HPP
#define VAR_OBJECT_HPP

class VariableObject {
 public:
  virtual void SetID(int id)                        = 0;
  virtual int GetID()                               = 0;

  virtual void SetInitialValue(int initial_value)   = 0;
  virtual int GetInitialValue()                     = 0;

  virtual void SetDecisionValue(int decision_value) = 0;
  virtual int GetDecisionValue()                    = 0;

  virtual void SetFinalValue(int final_value)       = 0;
  virtual int GetFinalValue()                       = 0;

 private:
  // int id_;
  // int initial_value_;
  // int decision_value_;
  // int final_value;
};

#endif  // VAR_OBJECT_HPP
