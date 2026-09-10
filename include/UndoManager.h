#pragma once
#include "Contact.h"
#include <stack>

enum class ActionType { ADD, UPDATE, DELETE };

struct UndoAction {
    ActionType type;
    Contact contactState; // Stores the state of the contact BEFORE the action
};

class UndoManager {
private:
    std::stack<UndoAction> undoStack;

public:
    void recordAction(ActionType type, const Contact& state) {
        undoStack.push({type, state});
    }

    bool hasActions() const { return !undoStack.empty(); }
    
    UndoAction popAction() {
        UndoAction action = undoStack.top();
        undoStack.pop();
        return action;
    }
};