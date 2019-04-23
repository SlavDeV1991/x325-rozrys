#ifndef UNDOSTACK_H
#define UNDOSTACK_H
#include <QUndoStack>

class UndoStack
{
public:
    UndoStack() = delete;
    static QUndoStack &Stack(void);
private:
    static QUndoStack m_undo_stack;
};

#endif // UNDOSTACK_H
