#ifndef MULTI_CAUSTIC_FUNCTION_H
#define MULTI_CAUSTIC_FUNCTION_H

#include "CausticFunction.h"

class CausticFunction;

class MultirangeCausticFunction : public PlotFunction
{
public:
    FUNC_ALIAS("MultirangeCaustic")
    FUNC_NAME(QT_TRANSLATE_NOOP("Function Name", "Multirange Caustic"))

    MultirangeCausticFunction(Schema *schema) : PlotFunction(schema) {}
    ~MultirangeCausticFunction() override;

    void calculate() override;
    bool hasOptions() const override { return true; }
    const char* iconPath() const override { return ":/toolbar/func_multi_caustic"; }
    int resultCount(Z::WorkPlane plane) const override;
    const PlotFuncResult& result(Z::WorkPlane plane, int index) const override;

    // Only needs for SP schemas
    void setPump(PumpParams* pump);

    QVector<Z::Variable> args() const;
    void setArgs(const QVector<Z::Variable>& args);

    const QList<CausticFunction*>& funcs() { return _funcs; }

    CausticFunction::Mode mode() const;
    void setMode(CausticFunction::Mode mode);

private:
    QList<CausticFunction*> _funcs;
};

#endif // MULTI_CAUSTIC_FUNCTION_H
