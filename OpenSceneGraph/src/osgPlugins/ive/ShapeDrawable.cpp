/**********************************************************************
 *
 *    FILE:            ShapeDrawable.cpp
 *
 *    DESCRIPTION:    Read/Write osg::ShapeDrawable in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerator
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 27.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Drawable.h"
#include "Exception.h"
#include "ShapeDrawable.h"
#include "Object.h"

using namespace ive;

void ShapeDrawable::write(DataOutputStream* out)
{
    // Write CullFace's identification.
    out->writeInt(IVESHAPEDRAWABLE);

    if ( out->getVersion() >= VERSION_0004 )
    {
        // If the osg class is inherited by any other class we should also write this to file.
        osg::Drawable*  drawable = dynamic_cast<osg::Drawable*>(this);
        if(drawable){
            ((ive::Drawable*)(drawable))->write(out);
        }
        else
            out_THROW_EXCEPTION("ShapeDrawable::write(): Could not cast this osg::ShapeDrawable to an osg::Object.");

    }
    else
    {
        osg::Object* obj = dynamic_cast<osg::Object*>(this);
        if(obj){
            ((ive::Object*)(obj))->write(out);
        }
        else
            out_THROW_EXCEPTION("ShapeDrawable::write(): Could not cast this osg::ShapeDrawable to an osg::Object.");
    }

    // Write ShapeDrawable's properties.
    out->writeVec4(getColor());

    if (getShape())
    {
        out->writeBool(true);
        out->writeShape(getShape());
    }
    else
    {
        out->writeBool(false);
    }
}

void ShapeDrawable::read(DataInputStream* in)
{
    // Peek on ShapeDrawable's identification.
    int id = in->peekInt();
    if(id == IVESHAPEDRAWABLE)
    {
        // Read ShapeDrawable's identification.
        id = in->readInt();

        if ( in->getVersion() >= VERSION_0004 )
        {
            // If the osg class is inherited by any other class we should also read this from file.
            osg::Drawable*  drawable = dynamic_cast<osg::Drawable*>(this);
            if(drawable){
                ((ive::Drawable*)(drawable))->read(in);
            }
            else
                in_THROW_EXCEPTION("ShapeDrawable::read(): Could not cast this osg::ShapeDrawable to an osg::Object.");
        }
        else
        {
            // If the osg class is inherited by any other class we should also read this from file.
            osg::Object*  obj = dynamic_cast<osg::Object*>(this);
            if(obj){
                ((ive::Object*)(obj))->read(in);
            }
            else
                in_THROW_EXCEPTION("ShapeDrawable::read(): Could not cast this osg::ShapeDrawable to an osg::Object.");
        }

        // Read ShapeDrawable's properties
        setColor(in->readVec4());

        if (in->readBool())
        {
            setShape(in->readShape());
        }

    }
    else
    {
        in_THROW_EXCEPTION("ShapeDrawable::read(): Expected ShapeDrawable identification.");
    }
}
