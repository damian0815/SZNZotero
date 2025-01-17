//
// SZNZoteroAPIClient.h
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
#if __IPHONE_OS_VERSION_MIN_REQUIRED
@import UIKit;
#endif
#import "AFOAuth1Client.h"

typedef NS_ENUM(NSUInteger, SZNZoteroAccessLevel) {
    SZNZoteroAccessNone,
    SZNZoteroAccessRead,
    SZNZoteroAccessReadWrite
};

/**
 `SZNZoteroAPIClient` is an HTTP client preconfigured for accessing Zotero API.
 */
@interface SZNZoteroAPIClient : AFOAuth1Client

/**
 The Altmetric identifier for the current user.
 */
@property (nonatomic, copy, nullable) NSString *userIdentifier;

/**
 The Altmetric username for the current user.
 */
@property (nonatomic, copy, nullable) NSString *username;

/**
 Whether the client is currently logged in.
 */
@property (readonly, nonatomic, getter = isLoggedIn) BOOL loggedIn;

@property (nonatomic, copy, nullable) NSNumber *lastModifiedVersion;

/**
 Initializes an `SZNZoteroAPIClient` object with the specified API key, secret, and URL scheme.

 @param key The API key.
 @param secret The API secret.
 @param URLScheme The URL scheme.

 @return The newly-initialized client.
 */
- (nonnull instancetype)initWithKey:(nonnull NSString *)key
                             secret:(nonnull NSString *)secret
                          URLScheme:(nonnull NSString *)URLScheme;

/**
 Authenticates the client with default access level parameters.
 
 @param success A block object to be executed when the authentication operations finish successfully. 
  This block has no return value and takes one argument: the newly-acquired OAuth token.
 @param failure A block object to be executed when the authentication operations finish unsuccessfully, or that finish successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)authenticateSuccess:(nonnull void (^)(AFOAuth1Token * __nullable token))success
                    failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Authenticates the client with the specified access level parameters.
 
 @param libraryAccess Whether the API should allow read access to personal library items.
 @param notesAccess Whether the API should allow read access to personal library notes.
 @param writeAccess Whether the API should allow write access to personal library.
 @param groupAccessLevel The level of access the API should allow to all current and future groups.
 @param webAuthorizationCallback A block object to be executed when the authentication process needs to prompt the user to provide its credentials.
  This block has no return value and takes one argument: the `NSURL` object for the authentication webpage.
 @param success A block object to be executed when the authentication operations finish successfully. 
  This block has no return value and takes one argument: the newly-acquired OAuth token.
 @param failure A block object to be executed when the authentication operations finish unsuccessfully, or that finish successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)authenticateWithLibraryAccess:(BOOL)libraryAccess
                          notesAccess:(BOOL)notesAccess
                          writeAccess:(BOOL)writeAccess
                     groupAccessLevel:(SZNZoteroAccessLevel)groupAccessLevel
             webAuthorizationCallback:(nullable void (^)(NSURL * __nonnull authenticationURL))webAuthorizationCallback
                              success:(nonnull void (^)(AFOAuth1Token * __nullable token))success
                              failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Creates an `AFHTTPRequestOperation` with a `GET` request, and enqueues it to the HTTP client’s operation queue.
 
 @param path The path to be appended to the HTTP client’s base URL and used as the request URL.
 @param parameters The parameters to be encoded and appended as the query string for the request URL.
 @param success A block object to be executed when the request operation finishes successfully. 
  This block has no return value and takes one argument: the object created from the response data.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)getPath:(nonnull NSString *)path
     parameters:(nullable NSDictionary *)parameters
        success:(nonnull void (^)(id __nullable responseObject))success
        failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Creates an `AFHTTPRequestOperation` with a `PUT` request, and enqueues it to the HTTP client’s operation queue.
 
 @param path The path to be appended to the HTTP client’s base URL and used as the request URL.
 @param parameters The parameters to be encoded and appended as the query string for the request URL.
 @param success A block object to be executed when the request operation finishes successfully. 
  This block has no return value and takes one argument: the object created from the response data.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)putPath:(nonnull NSString *)path
     parameters:(nullable NSDictionary *)parameters
        success:(nonnull void (^)(id __nullable responseObject))success
        failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Creates an `AFHTTPRequestOperation` with a `POST` request, and enqueues it to the HTTP client’s operation queue.
 
 @param path The path to be appended to the HTTP client’s base URL and used as the request URL.
 @param parameters The parameters to be encoded and appended as the query string for the request URL.
 @param headers The HTTP header parameters for the request URL.
 @param success A block object to be executed when the request operation finishes successfully. 
  This block has no return value and takes one argument: the object created from the response data of request.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)postPath:(nonnull NSString *)path
      parameters:(nullable NSDictionary *)parameters
         headers:(nullable NSDictionary *)headers
         success:(nonnull void (^)(id __nullable responseObject))success
         failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Creates an `AFHTTPRequestOperation` with a `PATCH` request, and enqueues it to the HTTP client’s operation queue.
 
 @param path The path to be appended to the HTTP client’s base URL and used as the request URL.
 @param parameters The parameters to be encoded and appended as the query string for the request URL.
 @param success A block object to be executed when the request operation finishes successfully.
  This block has no return value and takes one argument: the object created from the response data.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)patchPath:(nonnull NSString *)path
       parameters:(nullable NSDictionary *)parameters
          success:(nonnull void (^)(id __nullable responseObject))success
          failure:(nonnull void (^)(NSError * __nullable error))failure;

/**
 Creates an `AFHTTPRequestOperation` with a `DELETE` request, and enqueues it to the HTTP client’s operation queue.
 
 @param path The path to be appended to the HTTP client’s base URL and used as the request URL.
 @param parameters The parameters to be encoded and appended as the query string for the request URL.
 @param success A block object to be executed when the request operation finishes successfully. 
  This block has no return value and takes no argument.
 @param failure A block object to be executed when the request operation finishes unsuccessfully, or that finishes successfully, but encountered an error while parsing the response data. 
  This block has no return value and takes one argument: the `NSError` object describing the network or parsing error that occurred.
 */
- (void)deletePath:(nonnull NSString *)path
        parameters:(nullable NSDictionary *)parameters
           success:(nonnull void (^)())success
           failure:(nonnull void (^)(NSError * __nullable error))failure;

- (void)resetObserver;

- (NSMutableURLRequest *)nonAuthRequestWithMethod:(NSString *)method
											 path:(NSString *)path
									   parameters:(NSDictionary *)parameters;

@end


@interface NSData(SZNMD5)

- (nonnull NSString *)MD5;

@end


@interface NSString (SZNURLEncoding)

- (nonnull NSString *)szn_URLEncodedString;

@end
