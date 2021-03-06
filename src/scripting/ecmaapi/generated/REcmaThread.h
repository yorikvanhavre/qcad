// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMATHREAD_H
        #define RECMATHREAD_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "REcmaShellThread.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class QCADECMAAPI_EXPORT REcmaThread {

        public:
      static  void init(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getQThread(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        start
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        yieldCurrentThread
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        currentThreadAddress
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        currentThreadName
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        currentThread
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RThread* getSelf(const QString& fName, QScriptContext* context)
    ;static REcmaShellThread* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  void fromScriptValue(const QScriptValue& value,
        RThread*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RThread*>(o);
        }
    static  QScriptValue toScriptValue(QScriptEngine *engine,
        RThread*
        const &in){
            QScriptValue s = engine->newQObject(in, QScriptEngine::QtOwnership,
            QScriptEngine::PreferExistingWrapperObject);
            /*
            if(s.isNull()){
               REcmaHelper::throwError("This object is null.", engine->currentContext());
            }
            */
            return s;
        }
    };
    #endif
    