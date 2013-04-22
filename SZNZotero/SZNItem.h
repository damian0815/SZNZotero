//
// SZNItem.h
//
// Copyright (c) 2013 shazino (shazino SAS), http://www.shazino.com/
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

#import <Foundation/Foundation.h>
#import <TBXML.h>

@class SZNZoteroAPIClient, SZNAuthor;

/**
 `SZNItem` is a Zotero item.
 */
@interface SZNItem : NSObject

/**
 The item identifier.
 */
@property (copy, nonatomic) NSString *identifier;

/**
 The item author.
 */
@property (strong, nonatomic) SZNAuthor *author;

/**
 The item key.
 */
@property (copy, nonatomic) NSString *key;

/**
 The item title.
 */
@property (copy, nonatomic) NSString *title;

/**
 The item type.
 */
@property (copy, nonatomic) NSString *type;

/**
 The item version.
 */
@property (copy, nonatomic) NSString *version;

/**
 The item content.
 */
@property (strong, nonatomic) NSDictionary *content;

/**
 The item tags.
 */
@property (strong, nonatomic) NSSet *tags;

/**
 Parses an item from an API XML element.
 
 @param XMLElement A `TBXMLElement` representation of the API response.
 
 @return A `SZNItem` object.
 */
+ (SZNItem *)itemFromXMLElement:(TBXMLElement *)XMLElement;

/**
 Parses items from an API XML response.
 
 @param XML A `TBXML` representation of the API response.
 
 @return An array of `SZNItem` objects.
 */
+ (NSArray *)itemsFromXML:(TBXML *)XML;

/**
 Fetches all items in the current user library.
 
 @param client The API client to be used to send the fetch request.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes one argument: an array of `SZNItem` objects created from the response data of request.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
+ (void)fetchItemsInLibraryWithClient:(SZNZoteroAPIClient *)client success:(void (^)(NSArray *))success failure:(void (^)(NSError *))failure;

/**
 Fetches all top-level items in the current user library.
 
 @param client The API client to be used to send the fetch request.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes one argument: an array of `SZNItem` objects created from the response data of request.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
+ (void)fetchTopItemsInLibraryWithClient:(SZNZoteroAPIClient *)client success:(void (^)(NSArray *))success failure:(void (^)(NSError *))failure;

/**
 Fetches all child items under this item.
 
 @param client The API client to be used to send the fetch request.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes one argument: an array of `SZNItems` objects created from the response data of request.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)fetchChildItemsWithClient:(SZNZoteroAPIClient *)client success:(void (^)(NSArray *))success failure:(void (^)(NSError *))failure;

/**
 Updates item with new content.
 
 @param client The API client to be used to send the update request.
 @param partialContent The new content key/values.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes one argument: the updated `SZNItem` object.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)updateWithClient:(SZNZoteroAPIClient *)client content:(NSDictionary *)newContent success:(void (^)(SZNItem *))success failure:(void (^)(NSError *))failure;

/**
 Updates item with partial new content.
 
 @param client The API client to be used to send the update request.
 @param content The modified content key/values.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes one argument: the updated `SZNItem` object.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)updateWithClient:(SZNZoteroAPIClient *)client partialContent:(NSDictionary *)partialContent success:(void (^)(SZNItem *))success failure:(void (^)(NSError *))failure;

/**
 Deletes item.
 
 @param client The API client to be used to send the delete request.
 @param success A block object to be executed when the request operation finishes successfully. This block has no return value and takes no argument.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)deleteWithClient:(SZNZoteroAPIClient *)client success:(void (^)())success failure:(void (^)(NSError *))failure;

@end

