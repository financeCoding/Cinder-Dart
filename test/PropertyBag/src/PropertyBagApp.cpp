#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"

#include "cidart/DartVM.h"

#include <memory>
#include <map>

// TODO NEXT: Prop is in the bag, now I need to hook it up to toCinder and check it's map against the bag items
// - then comes the fun part: inferring types and auto decoding (when possible)

using namespace ci;
using namespace ci::app;
using namespace std;

template <typename T>
class Prop {
  public:
	Prop() {}
	Prop( T value )	: mValue( value ) {}
	virtual ~Prop() {}

	Prop<T>& operator=( T value ) { mValue = value; return *this; }

	const T&	value() const { return mValue; }
	T&			value() { return mValue; }

  	const T*		ptr() const { return &mValue; }
  	T*				ptr() { return &mValue; }

  private:
	T	mValue;
};

typedef shared_ptr<struct BagItemBase> BagItemBaseRef;

struct BagItemBase {
	BagItemBase( void *target, const string &label ) : mTarget( target ), mLabel( label ) {}

	void *mTarget;
	string mLabel; // TODO: this should probably be a property url
};

// this needs to take a reference to Prop::ptr(), which allows its value to be located. Analagous to Tween
template <typename T>
struct BagItem : BagItemBase {
	BagItem( T *target, const string &label ) : BagItemBase( &mTarget, label ) {}

//	T *mTarget;
};

class PropertyBag {
  public:
	template <typename T>
	void add( Prop<T> *prop, const string &label ) {
		BagItemBaseRef item( new BagItem<T>( prop->ptr(), label ) );

		mItems.insert( make_pair( prop->ptr(), item ) );
	}

private:
	multimap< void*, BagItemBaseRef>		mItems;
};


class PropertyBagApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	cidart::DartVM mDart;

	PropertyBag mBag;
	Prop<int> mIntProperty;
};

void PropertyBagApp::setup()
{
	mIntProperty = 3;
	mBag.add( &mIntProperty, "blarg" );

	mDart.loadScript( loadAsset( "main.dart" ) );

	gl::enableAlphaBlending();
}

void PropertyBagApp::mouseDown( MouseEvent event )
{
}

void PropertyBagApp::update()
{
}

void PropertyBagApp::draw()
{
	gl::clear();
	gl::drawStringCentered( string( "mIntProperty = " ) + toString( mIntProperty.value() ), getWindowCenter() );
}

CINDER_APP_NATIVE( PropertyBagApp, RendererGl )
