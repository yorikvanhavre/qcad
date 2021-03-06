// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMABLOCKLISTENERADAPTER_H
        #define RECMABLOCKLISTENERADAPTER_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RBlockListenerAdapter.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class QCADECMAAPI_EXPORT REcmaBlockListenerAdapter {

        public:
      static  void init(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getQObject(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRBlockListener(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;
        // properties of secondary base class RBlockListener:
        

        // methods of secondary base class RBlockListener:
        

    // properties:
    

    // public methods:
    static  QScriptValue
        updateBlocks
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clearBlocks
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RBlockListenerAdapter* getSelf(const QString& fName, QScriptContext* context)
    ;static RBlockListenerAdapter* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  void fromScriptValue(const QScriptValue& value,
        RBlockListenerAdapter*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RBlockListenerAdapter*>(o);
        }
    static  QScriptValue toScriptValue(QScriptEngine *engine,
        RBlockListenerAdapter*
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
    