//
//  MASUtilities.h
//  Masonry
//
//  Created by Jonas Budelmann on 19/08/13.
//  Copyright (c) 2013 Jonas Budelmann. All rights reserved.
//

#import <Foundation/Foundation.h>



#if TARGET_OS_IPHONE || TARGET_OS_TV

    #import <UIKit/UIKit.h>
    #define MAS_VIEW UIView
    #define MAS_VIEW_CONTROLLER UIViewController
    #define MASEdgeInsets UIEdgeInsets

    typedef UILayoutPriority MASLayoutPriority;
    static const MASLayoutPriority MASLayoutPriorityRequired = UILayoutPriorityRequired;
    static const MASLayoutPriority MASLayoutPriorityDefaultHigh = UILayoutPriorityDefaultHigh;
    static const MASLayoutPriority MASLayoutPriorityDefaultMedium = 500;
    static const MASLayoutPriority MASLayoutPriorityDefaultLow = UILayoutPriorityDefaultLow;
    static const MASLayoutPriority MASLayoutPriorityFittingSizeLevel = UILayoutPriorityFittingSizeLevel;

#elif TARGET_OS_MAC

    #import <AppKit/AppKit.h>
    #define MAS_VIEW NSView
    #define MASEdgeInsets NSEdgeInsets

    typedef NSLayoutPriority MASLayoutPriority;
    static const MASLayoutPriority MASLayoutPriorityRequired = NSLayoutPriorityRequired;
    static const MASLayoutPriority MASLayoutPriorityDefaultHigh = NSLayoutPriorityDefaultHigh;
    static const MASLayoutPriority MASLayoutPriorityDragThatCanResizeWindow = NSLayoutPriorityDragThatCanResizeWindow;
    static const MASLayoutPriority MASLayoutPriorityDefaultMedium = 501;
    static const MASLayoutPriority MASLayoutPriorityWindowSizeStayPut = NSLayoutPriorityWindowSizeStayPut;
    static const MASLayoutPriority MASLayoutPriorityDragThatCannotResizeWindow = NSLayoutPriorityDragThatCannotResizeWindow;
    static const MASLayoutPriority MASLayoutPriorityDefaultLow = NSLayoutPriorityDefaultLow;
    static const MASLayoutPriority MASLayoutPriorityFittingSizeCompression = NSLayoutPriorityFittingSizeCompression;

#endif

/**
 *	Allows you to attach keys to objects matching the variable names passed.
 *
 *  view1.mas_key = @"view1", view2.mas_key = @"view2";
 *
 *  is equivalent to:
 *
 *  MASAttachKeys(view1, view2);
 */
#define MASAttachKeys(...)                                                        \
    {                                                                             \
        NSDictionary *keyPairs = NSDictionaryOfVariableBindings(__VA_ARGS__);     \
        for (id key in keyPairs.allKeys) {                                        \
            id obj = keyPairs[key];                                               \
            NSAssert([obj respondsToSelector:@selector(setMas_key:)],             \
                     @"Cannot attach mas_key to %@", obj);                        \
            [obj setMas_key:key];                                                 \
        }                                                                         \
    }

/**
 *  Used to create object hashes
 *  Based on http://www.mikeash.com/pyblog/friday-qa-2010-06-18-implementing-equality-and-hashing.html
 */
#define MAS_NSUINT_BIT (CHAR_BIT * sizeof(NSUInteger))
#define MAS_NSUINTROTATE(val, howmuch) ((((NSUInteger)val) << howmuch) | (((NSUInteger)val) >> (MAS_NSUINT_BIT - howmuch)))

/**
 *  Given a scalar or struct value, wraps it in NSValue
 *  Based on EXPObjectify: https://github.com/specta/expecta
 */
static inline id _MASBoxValue(const char *type, ...) {
    va_list v;
    va_start(v, type);
    id obj = nil;
    if (strncmp(type, @encode(id), 1000) == 0) {
        id actual = va_arg(v, id);
        obj = actual;
    } else if (strncmp(type, @encode(CGPoint), 1000) == 0) {
        CGPoint actual = (CGPoint)va_arg(v, CGPoint);
        obj = [NSValue value:&actual withObjCType:type];
    } else if (strncmp(type, @encode(CGSize), 1000) == 0) {
        CGSize actual = (CGSize)va_arg(v, CGSize);
        obj = [NSValue value:&actual withObjCType:type];
    } else if (strncmp(type, @encode(MASEdgeInsets), 1000) == 0) {
        MASEdgeInsets actual = (MASEdgeInsets)va_arg(v, MASEdgeInsets);
        obj = [NSValue value:&actual withObjCType:type];
    } else if (strncmp(type, @encode(double), 1000) == 0) {
        double actual = (double)va_arg(v, double);
        obj = [NSNumber numberWithDouble:actual];
    } else if (strncmp(type, @encode(float), 1000) == 0) {
        float actual = (float)va_arg(v, double);
        obj = [NSNumber numberWithFloat:actual];
    } else if (strncmp(type, @encode(int), 1000) == 0) {
        int actual = (int)va_arg(v, int);
        obj = [NSNumber numberWithInt:actual];
    } else if (strncmp(type, @encode(long), 1000) == 0) {
        long actual = (long)va_arg(v, long);
        obj = [NSNumber numberWithLong:actual];
    } else if (strncmp(type, @encode(long long), 1000) == 0) {
        long long actual = (long long)va_arg(v, long long);
        obj = [NSNumber numberWithLongLong:actual];
    } else if (strncmp(type, @encode(short), 1000) == 0) {
        short actual = (short)va_arg(v, int);
        obj = [NSNumber numberWithShort:actual];
    } else if (strncmp(type, @encode(char), 1000) == 0) {
        char actual = (char)va_arg(v, int);
        obj = [NSNumber numberWithChar:actual];
    } else if (strncmp(type, @encode(bool), 1000) == 0) {
        bool actual = (bool)va_arg(v, int);
        obj = [NSNumber numberWithBool:actual];
    } else if (strncmp(type, @encode(unsigned char), 1000) == 0) {
        unsigned char actual = (unsigned char)va_arg(v, unsigned int);
        obj = [NSNumber numberWithUnsignedChar:actual];
    } else if (strncmp(type, @encode(unsigned int), 1000) == 0) {
        unsigned int actual = (unsigned int)va_arg(v, unsigned int);
        obj = [NSNumber numberWithUnsignedInt:actual];
    } else if (strncmp(type, @encode(unsigned long), 1000) == 0) {
        unsigned long actual = (unsigned long)va_arg(v, unsigned long);
        obj = [NSNumber numberWithUnsignedLong:actual];
    } else if (strncmp(type, @encode(unsigned long long), 1000) == 0) {
        unsigned long long actual = (unsigned long long)va_arg(v, unsigned long long);
        obj = [NSNumber numberWithUnsignedLongLong:actual];
    } else if (strncmp(type, @encode(unsigned short), 1000) == 0) {
        unsigned short actual = (unsigned short)va_arg(v, unsigned int);
        obj = [NSNumber numberWithUnsignedShort:actual];
    }
    va_end(v);
    return obj;
}

#define MASBoxValue(value) _MASBoxValue(@encode(__typeof__((value))), (value))
