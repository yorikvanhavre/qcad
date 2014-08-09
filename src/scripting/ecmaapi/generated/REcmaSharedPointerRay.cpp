// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #include "REcmaSharedPointerRay.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RBox.h"
            
                #include "RPolyline.h"
            
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaSharedPointerXLine.h"
                 void REcmaSharedPointerRay::init(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RRayPointer*) 0)));
        protoCreated = true;
    }

    
        // primary base class RXLine:
        
            proto->setPrototype(engine.defaultPrototype(
            qMetaTypeId<RXLinePointer>()));
          
        /*
        
        */
    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    
    // copy:
    REcmaHelper::registerFunction(&engine, proto, copy, "copy");
    
        // shared pointer support:
        REcmaHelper::registerFunction(&engine, proto, data, "data");
        

        REcmaHelper::registerFunction(&engine, proto, isNull, "isNull");
        

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    
        // conversion for base class RXLine
        REcmaHelper::registerFunction(&engine, proto, getRXLine, "getRXLine");
        
        // conversion for base class RShape
        REcmaHelper::registerFunction(&engine, proto, getRShape, "getRShape");
        
        // conversion for base class RDirected
        REcmaHelper::registerFunction(&engine, proto, getRDirected, "getRDirected");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, clone, "clone");
            
            REcmaHelper::registerFunction(&engine, proto, trimEndPoint, "trimEndPoint");
            
            REcmaHelper::registerFunction(&engine, proto, getPointsWithDistanceToEnd, "getPointsWithDistanceToEnd");
            
            REcmaHelper::registerFunction(&engine, proto, reverse, "reverse");
            
            REcmaHelper::registerFunction(&engine, proto, getClippedLine, "getClippedLine");
            
            REcmaHelper::registerFunction(&engine, proto, getVectorTo, "getVectorTo");
            
            REcmaHelper::registerFunction(&engine, proto, stretch, "stretch");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RRayPointer>(), *proto);
      
    

    QScriptValue ctor = engine.newFunction(create, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RRayPointer",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaSharedPointerRay::create(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RRay(): Did you forget to construct with 'new'?"),
           context);
    }

    QScriptValue result;
        
            // generate constructor variants:
            
    if( context->argumentCount() ==
        0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RRay
                    cppResult;
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    if( context->argumentCount() ==
        1
                && (
                
                        context->argument(
                        0
                        ).isVariant()
                        ||
                    
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: RLine */
            
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RLine*
                    ap0 =
                    qscriptvalue_cast<
                    RLine*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RLine.",
                               context);                    
                    }
                    RLine 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RRay
                    cppResult(
                    a0
                    );
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    if( context->argumentCount() ==
        2
                && (
                
                        context->argument(
                        0
                        ).isVariant()
                        ||
                    
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: RVector */
            
                && (
                
                        context->argument(
                        1
                        ).isVariant()
                        ||
                    
                        context->argument(
                        1
                        ).isQObject()
                        ||
                    
                        context->argument(
                        1
                        ).isNull()
                ) /* type: RVector */
            
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap1 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if (ap1 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 1 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a1 = 
                    *ap1;
                
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RRay
                    cppResult(
                    a0
        ,
    a1
                    );
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    if( context->argumentCount() ==
        3
                && (
                
                        context->argument(
                        0
                        ).isVariant()
                        ||
                    
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: RVector */
            
                && (
                
                        context->argument(
                        1
                        ).isNumber()
                ) /* type: double */
            
                && (
                
                        context->argument(
                        2
                        ).isNumber()
                ) /* type: double */
            
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    double
                    a1 =
                    (double)
                    
                    context->argument( 1 ).
                    toNumber();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RRay
                    cppResult(
                    a0
        ,
    a1
        ,
    a2
                    );
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RRay(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaSharedPointerRay::getRXLine(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RXLine* cppResult =
                    qscriptvalue_cast<RRay*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaSharedPointerRay::getRShape(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RShape* cppResult =
                    qscriptvalue_cast<RRay*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaSharedPointerRay::getRDirected(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RDirected* cppResult =
                    qscriptvalue_cast<RRay*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaSharedPointerRay::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RRay"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaSharedPointerRay::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("RXLine");
    
        list.append("RShape");
    
        list.append("RDirected");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaSharedPointerRay::clone
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::clone", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::clone";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("clone", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'RRay *'
    RRay * cppResult =
        
               self->clone();
        // return type: RRay *
                // pointer, copyable 
                result = qScriptValueFromValue(engine, *cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.clone().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::clone", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::trimEndPoint
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::trimEndPoint", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::trimEndPoint";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("trimEndPoint", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->trimEndPoint(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.trimEndPoint().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::trimEndPoint", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::getPointsWithDistanceToEnd
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::getPointsWithDistanceToEnd", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::getPointsWithDistanceToEnd";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("getPointsWithDistanceToEnd", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isNumber()
        ) /* type: double */
     && (
            context->argument(1).isNumber()
        ) /* type: RS::From */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    double
                    a0 =
                    (double)
                    
                    context->argument( 0 ).
                    toNumber();
                
                    // argument isStandardType
                    RS::From
                    a1 =
                    (RS::From)
                    (int)
                    context->argument( 1 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'QList < RVector >'
    QList < RVector > cppResult =
        
               self->getPointsWithDistanceToEnd(a0
        ,
    a1);
        // return type: QList < RVector >
                // List of ...:
                result = REcmaHelper::listToScriptValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.getPointsWithDistanceToEnd().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::getPointsWithDistanceToEnd", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::reverse
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::reverse", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::reverse";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("reverse", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'bool'
    bool cppResult =
        
               self->reverse();
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.reverse().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::reverse", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::getClippedLine
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::getClippedLine", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::getClippedLine";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("getClippedLine", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RBox */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RBox*
                    ap0 =
                    qscriptvalue_cast<
                    RBox*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RBox.",
                               context);                    
                    }
                    RBox 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ function:
    // return type 'RLine'
    RLine cppResult =
        
               self->getClippedLine(a0);
        // return type: RLine
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.getClippedLine().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::getClippedLine", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::getVectorTo
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::getVectorTo", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::getVectorTo";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("getVectorTo", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ function:
    // return type 'RVector'
    RVector cppResult =
        
               self->getVectorTo(a0);
        // return type: RVector
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isBool()
        ) /* type: bool */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    bool
                    a1 =
                    (bool)
                    
                    context->argument( 1 ).
                    toBool();
                
    // end of arguments

    // call C++ function:
    // return type 'RVector'
    RVector cppResult =
        
               self->getVectorTo(a0
        ,
    a1);
        // return type: RVector
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.getVectorTo().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::getVectorTo", context, engine);
            return result;
        }
         QScriptValue
        REcmaSharedPointerRay::stretch
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaSharedPointerRay::stretch", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaSharedPointerRay::stretch";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RRay* self = 
                        getSelf("stretch", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RPolyline */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RVector */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RPolyline*
                    ap0 =
                    qscriptvalue_cast<
                    RPolyline*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 0 is not of type RPolyline.",
                               context);                    
                    }
                    RPolyline 
                    a0 = 
                    *ap0;
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap1 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if (ap1 == NULL) {
                           return REcmaHelper::throwError("RRay: Argument 1 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a1 = 
                    *ap1;
                
    // end of arguments

    // call C++ function:
    // return type 'bool'
    bool cppResult =
        
               self->stretch(a0
        ,
    a1);
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RRay.stretch().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaSharedPointerRay::stretch", context, engine);
            return result;
        }
         QScriptValue REcmaSharedPointerRay::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RRay* self = getSelf("toString", context);
    
    QString result;
    
            QDebug d(&result);
            if (self!=NULL) {
                d << *self;
            }
            else {
                d << "NULL";
            }
        
    return QScriptValue(result);
    }
     QScriptValue REcmaSharedPointerRay::copy
    (QScriptContext *context, QScriptEngine *engine)
    
    {
        RRay cp = qscriptvalue_cast<RRay>(context->thisObject());
        return qScriptValueFromValue(engine, cp);
    }
     QScriptValue REcmaSharedPointerRay::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RRay* self = getSelf("RRay", context);
        //Q_ASSERT(self!=NULL);
        if (self==NULL) {
            return REcmaHelper::throwError("self is NULL", context);
        }
        
    
        delete self;
        context->thisObject().setData(engine->nullValue());
        context->thisObject().prototype().setData(engine->nullValue());
        context->thisObject().setPrototype(engine->nullValue());
        context->thisObject().setScriptClass(NULL);
        return engine->undefinedValue();
    }
    RRay* REcmaSharedPointerRay::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RRay* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RRayPointer >(context->thisObject())
                
                    ->data()
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RRay.%1(): "
                        "This object is not a RRay").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RRay* REcmaSharedPointerRay::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RRay* selfBase = getSelf(fName, context);
                RRay* self = dynamic_cast<RRay*>(selfBase);
                //return REcmaHelper::scriptValueTo<RRay >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RRay.%1(): "
                    "This object is not a RRay").arg(fName),
                    context);
            }

            return self;
            


        }
         QScriptValue REcmaSharedPointerRay::data
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RRay* self = getSelf("data", context);
    return qScriptValueFromValue(engine, self);
    }
     QScriptValue REcmaSharedPointerRay::isNull
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RRayPointer* self = REcmaHelper::scriptValueTo<RRayPointer >(context->thisObject());

    //RRay* self = getSelf("isNull", context);
    //Q_ASSERT(self!=NULL);
    if (self==NULL) {
        return REcmaHelper::throwError("self is NULL", context);
    }
    return qScriptValueFromValue(engine, self->isNull());
    }
    