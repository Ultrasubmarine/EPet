//
//  IRender.hpp
//  EPet
//
//  Created by marina porkhunova on 03.08.2024.
//

#ifndef IRender_h
#define IRender_h

#include <stdio.h>
#include <set>

#include "IWindow.h"

struct Rect;
class IWindow;

//struct Rect
//{
//    int x,y;
//    int w,h;
//};

struct RenderObject
{
    int sorting;
    
   // std::shared_ptr<Texture> texture;
    void* info; // dest rect, rotation, and etc.
};

struct RenderObjectCmp
{
    bool operator()(const RenderObject& lobj, const RenderObject& robj) const
    {
        return lobj.sorting < robj.sorting;
    }
};

class IRender
{
  //  std::multimap<int, std::weak_ptr<RenderObject>> _renderObjects;
    
public:
    virtual ~IRender() {};
    virtual void* Init(IWindow* w) = 0;
    virtual void Deinit() = 0;
    
    virtual void Clear() = 0;
    void Draw() {}; 
//    virtual void Draw( std::iterator_traits<Rect> begin, std::iterator_traits<InputIt> end) = 0;
    virtual void Present() = 0;
    
    virtual bool IsRenderExist() = 0;
    
  //  void AddRenderObject(int sorting, RenderObject* obj);
  //  void RemoveRenderObject(RenderObject* obj);
};


//void IRender::AddRenderObject(int sorting, RenderObject* obj)
//{
//  //  _renderObjects.emplace(sorting, obj);
//}
//
//void IRender::RemoveRenderObject(RenderObject* obj)
//{
//   // _renderObjects.erase(obj);
//   // std::find(_renderObjects.begin(), _renderObjects.end(), )
//}

#endif /* IRender_h */
