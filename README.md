# UIView-ParentController

##如何获取到View所在的控制器
---
有些时候我们在一个View中需要一些操作，push到某个Controller。
如po主这个Demo，有几种不同的帖子信息，需要分开展示，所以上面楼主的信息自定义了一个View，用来展示组队类型的帖子。
![](http://ww3.sinaimg.cn/mw690/6986863ejw1f6j1ate3gvj20hz0ur41r.jpg)
在这个View中有一个静态的TableView来展示一系列的组队信息，其中总人数这一行，如果点击之后会push到一个新的Controller来展示申请用户的信息。

这个跳转改如何实现？我问了一些面试者，他们的回答普遍是通过block或者代理，来让这个自定义的View跳转，这并不是我想要的答案呀T.T其实我想问的是如何通过这个自定义的TableHeaderView来获取到它父控件的Controller以及NavigationController，但是没有人想到该如何实现…吐槽一下

废话少说，要想获取到一个View所在的控制器，需要对响应者链条有一定的了解，不懂的童鞋可以Google一下。在这里我提供一个UIView的分类供大家使用，导入之后只需要`view.parentController`就可以轻松的获取到View所在的控制器了

```objc
#import <UIKit/UIKit.h>

@interface UIView (ParentController)

/** 这个方法通过响应者链条获取view所在的控制器 */
- (UIViewController *)parentController;

/** 这个方法通过响应者链条获取view所在的控制器 */
+ (UIViewController *)currentViewController;

@end
```

```objc
//1.提供一个UIView的分类方法，这个方法通过响应者链条获取view所在的控制器
- (UIViewController *)parentController

{
    UIResponder *responder = [self nextResponder];
    while (responder) {
        
        if ([responder isKindOfClass:[UIViewController class]]) {
            return (UIViewController *)responder;
        }
        responder = [responder nextResponder];
    }
    return nil;
}

//2.通过控制器的布局视图可以获取到控制器实例对象(modal的展现方式需要取到控制器的根视图)
+ (UIViewController *)currentViewController {
    
    UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
    
    // modal展现方式的底层视图不同
    
    // 取到第一层时，取到的是UITransitionView，通过这个view拿不到控制器
    UIView *firstView = [keyWindow.subviews firstObject];
    UIView *secondView = [firstView.subviews firstObject];
    UIViewController *vc = secondView.parentController;
    
    if ([vc isKindOfClass:[UITabBarController class]]) {
        
        UITabBarController *tab = (UITabBarController *)vc;
        
        if ([tab.selectedViewController isKindOfClass:[UINavigationController class]]) {
            
            UINavigationController *nav = (UINavigationController *)tab.selectedViewController;
            
            return [nav.viewControllers lastObject];
            
        } else {
            
            return tab.selectedViewController;
            
        }
        
    } else if([vc isKindOfClass:[UINavigationController class]]) {
        
        UINavigationController *nav = (UINavigationController *)vc;
        
        return [nav.viewControllers lastObject];
        
    } else {
        
        return vc;
        
    }
    
    return nil;
}

//

- (UIViewController *)getCurrentVC

{
    
    UIViewController *result = nil;
    
    UIWindow * window = [[UIApplication sharedApplication] keyWindow];
    
    if (window.windowLevel != UIWindowLevelNormal) {
        
        NSArray *windows = [[UIApplication sharedApplication] windows];
        
        for(UIWindow * tmpWin in windows) {
            
            if (tmpWin.windowLevel == UIWindowLevelNormal)
                
            {
                
                window = tmpWin;
                
                break;
                
            }
            
        }
        
    }
    
    UIView *frontView = [[window subviews] objectAtIndex:0];
    
    id nextResponder = [frontView nextResponder];
    
    if ([nextResponder isKindOfClass:[UIViewController class]])
        
        result = nextResponder;
    
    else
        
        result = window.rootViewController;
    
    return result;
    
}
```

## GitHub
---
点这里直接带走[GitHub](https://github.com/icebacky/UIView-ParentController)
