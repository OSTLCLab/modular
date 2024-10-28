// This file is part of arduino-fsm.
//
// arduino-fsm is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// arduino-fsm is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with arduino-fsm.  If not, see <http://www.gnu.org/licenses/>.

// Removed time-based transitions for simplicity and to avoid Arduino dependency
// and according time-based issues.

#include "Fsm.h"

State::State(void (*on_enter)(), void (*on_state)(), void (*on_exit)())
: on_enter(on_enter),
  on_state(on_state),
  on_exit(on_exit)
{
}


Fsm::Fsm(State* initial_state)
: m_current_state(initial_state),
  m_transitions(nullptr),
  m_num_transitions(0),
  m_initialized(false)
{
}


Fsm::~Fsm()
{
  delete[] m_transitions;
  m_transitions = nullptr;
}

Fsm::Transition* Fsm::_realloc(Transition* arr, size_t oldSize, size_t newSize) {
    Transition* newArr = new Transition[newSize];
    size_t sizeToCopy = (oldSize < newSize) ? oldSize : newSize;
    for (size_t i = 0; i < sizeToCopy; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;  // Free the old memory
    return newArr; // Return the resized array
}

void Fsm::add_transition(State* state_from, State* state_to, int event,
                         void (*on_transition)())
{
  if (state_from == nullptr || state_to == nullptr)
    return;

  Transition transition = Fsm::create_transition(state_from, state_to, event,
                                               on_transition);
  m_transitions = (Transition*) _realloc(m_transitions, m_num_transitions * sizeof(Transition), (m_num_transitions + 1) * sizeof(Transition));
  
  m_transitions[m_num_transitions] = transition;
  m_num_transitions++;
}

Fsm::Transition Fsm::create_transition(State* state_from, State* state_to,
                                       int event, void (*on_transition)())
{
  Transition t;
  t.state_from = state_from;
  t.state_to = state_to;
  t.event = event;
  t.on_transition = on_transition;

  return t;
}

void Fsm::trigger(int event)
{
  if (m_initialized)
  {
    // Find the transition with the current state and given event.
    for (int i = 0; i < m_num_transitions; ++i)
    {
      if (m_transitions[i].state_from == m_current_state &&
          m_transitions[i].event == event)
      {
        Fsm::make_transition(&(m_transitions[i]));
        return;
      }
    }
  }
}

void Fsm::run_machine()
{
  // first run must exec first state "on_enter"
  if (!m_initialized)
  {
    m_initialized = true;
    if (m_current_state->on_enter != nullptr)
      m_current_state->on_enter();
  }
  
  if (m_current_state->on_state != nullptr)
    m_current_state->on_state();
    
}

void Fsm::make_transition(Transition* transition)
{
 
  // Execute the handlers in the correct order.
  if (transition->state_from->on_exit != nullptr)
    transition->state_from->on_exit();

  if (transition->on_transition != nullptr)
    transition->on_transition();

  if (transition->state_to->on_enter != nullptr)
    transition->state_to->on_enter();
  
  m_current_state = transition->state_to;

}
