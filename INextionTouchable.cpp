#include "INextionTouchable.h"

INextionTouchable::INextionTouchable(Nextion &nex, uint8_t page,
                                     uint8_t component, const char *name)
    : INextionWidget(nex, page, component, name)
{
  nex.registerTouchable(this);
}

bool INextionTouchable::processEvent(uint8_t pageID, uint8_t componentID,
                                     uint8_t eventType)
{
  if (pageID != m_pageID)
    return false;

  if (componentID != m_componentID)
    return false;

  switch (eventType)
  {
  case NEX_EVENT_PUSH:
    if (m_pressEvent)
      (*m_pressEvent)(this);
    return true;

  case NEX_EVENT_POP:
    if (m_releaseEvent)
      (*m_releaseEvent)(this);
    return true;

  default:
    return false;
  }
}

bool INextionTouchable::attachPressEvent(NextionCallbackHandler::NextionFunction cb)
{
  if (!cb)
    return false;
  
  if (m_pressEvent != NULL)
    detachPressEvent();

  m_pressEvent = new NextionCallbackHandler(cb, NEX_EVENT_PUSH);
  return true;
}

bool INextionTouchable::attachPressEvent(INextionCallback *obj)
{
  if (!obj)
    return false;
  
  if (m_pressEvent != NULL)
    detachPressEvent();

  m_pressEvent = new NextionCallbackHandler(obj, NEX_EVENT_PUSH);
  return true;
}

void INextionTouchable::detachPressEvent()
{
  if(m_pressEvent != NULL)
    delete m_pressEvent;

  m_pressEvent = NULL;
}

bool INextionTouchable::attachReleaseEvent(NextionCallbackHandler::NextionFunction cb)
{
  if (!cb)
    return false;
    
  if (m_releaseEvent != NULL)
    detachReleaseEvent();

  m_releaseEvent = new NextionCallbackHandler(cb, NEX_EVENT_POP);
  return true;
}

bool INextionTouchable::attachReleaseEvent(INextionCallback *obj)
{
  if (!obj)
    return false;
  
  if (m_releaseEvent != NULL)
    detachReleaseEvent();

  m_releaseEvent = new NextionCallbackHandler(obj, NEX_EVENT_POP);
  return true;
}

void INextionTouchable::detachReleaseEvent()
{
  if(m_releaseEvent != NULL)
    delete m_releaseEvent;

  m_releaseEvent = NULL;
}
