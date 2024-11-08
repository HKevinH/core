#pragma once
#include <QLineEdit>

#include "Extras/Export/export.h"
#include "QtWidgets/QWidget/qwidget_macro.h"
#include "core/NodeWidget/nodewidget.h"

class DLL_EXPORT NLineEdit : public QLineEdit, public NodeWidget
{
    Q_OBJECT
    NODEWIDGET_IMPLEMENTATIONS(QLineEdit)
  public:
    using QLineEdit::QLineEdit; // inherit all constructors of QLineEdit

    virtual void connectSignalsToEventEmitter()
    {
        QWIDGET_SIGNALS
        // Qt Connects: Implement all signal connects here
        QObject::connect(this, &QLineEdit::cursorPositionChanged, [=](int oldPost, int newPos) {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onCursorPositionChange"), Napi::Value::From(env, oldPost),
                                   Napi::Value::From(env, newPos)});
        });
        QObject::connect(this, &QLineEdit::editingFinished, [=]() {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onEditingFinish")});
        });
        QObject::connect(this, &QLineEdit::inputRejected, [=]() {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onInputReject")});
        });
        QObject::connect(this, &QLineEdit::returnPressed, [=]() {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onReturnPress")});
        });
        QObject::connect(this, &QLineEdit::selectionChanged, [=]() {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onSelectionChange")});
        });
        QObject::connect(this, &QLineEdit::textChanged, [=](QString text) {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onTextChange"), Napi::Value::From(env, text.toStdString())});
        });
        QObject::connect(this, &QLineEdit::textEdited, [=](QString text) {
            Napi::Env env = this->emitOnNode.Env();
            Napi::HandleScope scope(env);
            this->emitOnNode.Call({Napi::String::New(env, "onTextEdit"), Napi::Value::From(env, text.toStdString())});
        });
    }
};