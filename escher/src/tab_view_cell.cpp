#include <escher/tab_view_cell.h>
#include <escher/palette.h>
extern "C" {
#include <assert.h>
}

TabViewCell::TabViewCell() :
  View(),
  m_active(false),
  m_selected(false),
  m_name(nullptr)
{
}

void TabViewCell::setName(const char * name) {
  m_name = name;
  markRectAsDirty(bounds());
}

void TabViewCell::setActive(bool active) {
  m_active = active;
  markRectAsDirty(bounds());
}

void TabViewCell::setSelected(bool selected) {
  m_selected = selected;
  markRectAsDirty(bounds());
}

KDSize TabViewCell::minimalSizeForOptimalDisplay() const {
  return KDText::stringSize(m_name, KDText::FontSize::Small);
}

void TabViewCell::drawRect(KDContext * ctx, KDRect rect) const {
  KDCoordinate height = bounds().height();
  KDCoordinate width = bounds().width();
  // choose the background color
  KDColor text = m_active ? Palette::PurpleBright : KDColorWhite;
  KDColor background = m_active ? KDColorWhite : Palette::PurpleBright;
  background = m_selected ? Palette::Select : background;
  // Color the background according to the state of the tab cell
  if (m_active || m_selected) {
    ctx->fillRect(KDRect(0, 0, width, 1), Palette::PurpleBright);
    ctx->fillRect(KDRect(0, 1, width, height-1), background);
  } else {
    ctx->fillRect(KDRect(0, 0, width, height), background);
  }
  // Write title
  KDSize textSize = KDText::stringSize(m_name, KDText::FontSize::Small);
  KDPoint origin(0.5f*(m_frame.width() - textSize.width()),0.5f*(m_frame.height() - textSize.height()));
  ctx->drawString(m_name, origin, KDText::FontSize::Small, text, background);
}

#if ESCHER_VIEW_LOGGING
const char * TabViewCell::className() const {
  return "TabViewCell";
}

void TabViewCell::logAttributes(std::ostream &os) const {
  View::logAttributes(os);
  os << " active=\"" << m_active << "\"";
  os << " name=\"" << m_name << "\"";
}
#endif
