#include <fstream>
#include <iostream>
#include <sstream>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression
{
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}

  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }

  virtual long evaluate() const { return num; }
};

class InfoExpression : public Expression
{
 protected:
  std::string word;       // literal expression
  Expression *lhs, *rhs;  // pointer to use poly
 public:
  InfoExpression(std::string str, Expression * lhs, Expression * rhs) :
      word(str),
      lhs(lhs),
      rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << '(' << lhs->toString() << ' ' << word << ' ' << rhs->toString() << ')';
    return ss.str();
  }
  virtual ~InfoExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public InfoExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : InfoExpression("+", lhs, rhs) {}

  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public InfoExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : InfoExpression("-", lhs, rhs) {}

  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public InfoExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : InfoExpression("*", lhs, rhs) {}

  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public InfoExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : InfoExpression("/", lhs, rhs) {}

  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};
