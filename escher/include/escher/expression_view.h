#ifndef ESCHER_EXPRESSION_VIEW_H
#define ESCHER_EXPRESSION_VIEW_H

#include <escher/view.h>
#include <kandinsky/color.h>
#include <poincare/expression_layout.h>

/* This class does not handle the expression layout as the size of the layout is
 * needed to compute the size of table cells hosting the expression. As the size
 * of this cell is determined before we set the expression in the expression
 * view, we cannot use minimalSizeForOptimalDisplay to assess the required
 * size. */

class ExpressionView : public View {
public:
  ExpressionView(float horizontalAlignment = 0.0f, float verticalAlignment = 0.5f,
    KDColor textColor = KDColorBlack, KDColor backgroundColor = KDColorWhite);
  void setExpression(Poincare::ExpressionLayout * expressionLayout);
  void drawRect(KDContext * ctx, KDRect rect) const override;
  void setBackgroundColor(KDColor backgroundColor);
  void setTextColor(KDColor textColor);
  void setAlignment(float horizontalAlignment, float verticalAlignment);
  KDSize minimalSizeForOptimalDisplay() override;
private:
  Poincare::ExpressionLayout * m_expressionLayout;
  float m_horizontalAlignment;
  float m_verticalAlignment;
  KDColor m_textColor;
  KDColor m_backgroundColor;
};

#endif
