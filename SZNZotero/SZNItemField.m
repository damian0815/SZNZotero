//
// SZNItemField.m
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

#import "SZNItemField.h"

#import "SZNZoteroAPIClient.h"
#import "SZNItemType.h"


@implementation SZNItemField

#pragma mark - Initializer

- (nonnull instancetype)initWithField:(nonnull NSString *)field
                        localizedName:(nonnull NSString *)localizedName {
    self = [super init];

    if (self) {
        self.field = field;
        self.localizedName = localizedName;
    }

    return self;
}

+ (nullable instancetype)itemFieldWithResponseDictionary:(nonnull NSDictionary *)responseDictionary {
    NSString *field = responseDictionary[@"field"];
    NSString *localized = responseDictionary[@"localized"];

    if (field == nil || localized == nil) {
        return nil;
    }

    return [[self alloc] initWithField:field localizedName:localized];
}

+ (nonnull NSArray <SZNItemField *> *)itemFieldsWithResponseArray:(nonnull NSArray *)responseArray {
    NSMutableArray *itemFields = [[NSMutableArray alloc] initWithCapacity:[responseArray count]];

    for (NSDictionary *rawItemField in responseArray) {
        if ([rawItemField isKindOfClass:[NSDictionary class]] == NO) {
            continue;
        }

        SZNItemField *itemField = [SZNItemField itemFieldWithResponseDictionary:rawItemField];
        if (itemField) {
            [itemFields addObject:itemField];
        }
    }

    return itemFields;
}

#pragma mark - Fetch

+ (void)fetchValidFieldsWithClient:(nonnull SZNZoteroAPIClient *)client
                       forItemType:(nonnull SZNItemType *)itemType
                           success:(nonnull void (^)(NSArray <SZNItemField *> * __nonnull validFields))success
                           failure:(nullable void (^)(NSError * __nullable error))failure {
    [client
     getPath:@"/itemTypeFields"
     parameters:@{@"itemType": itemType.type}
     success:^(id responseObject) {
         if ([responseObject isKindOfClass:NSArray.class] == NO) {
             if (failure) {
                 failure(nil);
             }

             return;
         }

         NSArray *itemFields = [self itemFieldsWithResponseArray:responseObject];
         success(itemFields);
     }
     failure:failure];
}

@end
