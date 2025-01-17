//
// SZNItemType.h
//
// Copyright (c) 2013-2016 shazino (shazino SAS), http://www.shazino.com/
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

@import Foundation;

@class SZNZoteroAPIClient;

/**
 The link mode for attachement items.
 */
typedef NS_ENUM(NSUInteger, SZNAttachmentLinkMode) {
    SZNAttachmentLinkModeImportedFile,
    SZNAttachmentLinkModeImportedURL,
    SZNAttachmentLinkModeLinkedFile,
    SZNAttachmentLinkModeLinkedURL
};


/**
 The item type describes the format of an item.

 API documentation: https://www.zotero.org/support/dev/web_api/v3/types_and_fields
 */
@interface SZNItemType : NSObject

/**
 The identifier value of the type.
 */
@property (nonatomic, copy, nonnull) NSString *type;

/**
 The localized name of the type.
 */
@property (nonatomic, copy, nonnull) NSString *localizedName;


/// @name Initialization

/**
 Default `NSObject` initializer, not available.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 Designated initializer. Implemented by subclasses to initialize a new object (the receiver) immediately after memory for it has been allocated.

 @param type          The identifier value of the type.
 @param localizedName The localized name of the type.

 @return An initialized object.
 */
- (nonnull instancetype)initWithType:(nonnull NSString *)type
                       localizedName:(nonnull NSString *)localizedName NS_DESIGNATED_INITIALIZER;

/**
 Factory initializer for an object based on the API response dictionary.

 @param responseDictionary The dictionary generated from the Zotero API server response.

 @return The newly-created and configured object.
 */
+ (nullable instancetype)itemTypeWithResponseDictionary:(nonnull NSDictionary *)responseDictionary;


/// @name API requests

/**
 Fetches the valid item types.

 @param client  The API client.
 @param success A block object to be executed when the request operation finishes successfully.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data.
 */
+ (void)fetchTypesWithClient:(nonnull SZNZoteroAPIClient *)client
                     success:(nonnull void (^)(NSArray <SZNItemType *> * __nonnull))success
                     failure:(nullable void (^)(NSError * __nullable error))failure;

/**
 Fetches the new items template for a given item type.

 @param client   The API client.
 @param itemType The item type for which to fetch the template.
 @param success  A block object to be executed when the request operation finishes successfully.
 @param failure  A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data.
 */
+ (void)fetchNewItemTemplateWithClient:(nonnull SZNZoteroAPIClient *)client
                               forType:(nonnull SZNItemType *)itemType
                               success:(nonnull void (^)(NSDictionary * __nonnull responseObject))success
                               failure:(nullable void (^)(NSError * __nullable error))failure;

/**
 Fetches the new attachment template for a given link mode.

 @param client   The API client.
 @param linkMode The link mode for which to fetch the template.
 @param success  A block object to be executed when the request operation finishes successfully.
 @param failure  A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data.
 */
+ (void)fetchNewAttachmentTemplateWithClient:(nonnull SZNZoteroAPIClient *)client
                                    linkMode:(SZNAttachmentLinkMode)linkMode
                                     success:(nonnull void (^)(NSDictionary * __nonnull responseObject))success
                                     failure:(nullable void (^)(NSError * __nullable error))failure;

/**
 Returns the identifier value for a given link mode.

 @param linkMode The link mode of the item.

 @return The link mode value.
 */
+ (nonnull NSString *)valueForLinkMode:(SZNAttachmentLinkMode)linkMode;

@end
