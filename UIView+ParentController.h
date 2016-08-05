//
//  UIView+ParentController.h
//  HUD
//
//  Created by 韩啸宇 on 16/3/29.
//  Copyright © 2016年 hxy. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (ParentController)
/** 这个方法通过响应者链条获取view所在的控制器 */
- (UIViewController *)parentController;
/** 这个方法通过响应者链条获取view所在的控制器 */
+ (UIViewController *)currentViewController;
@end
