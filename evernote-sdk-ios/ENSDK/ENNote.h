/*
 * Copyright (c) 2014 by Evernote Corporation, All rights reserved.
 *
 * Use of the source code and binary libraries included in this package
 * is permitted under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
@class ENNote;
@class ENResource;
@class ENNotebook;

extern NSString * const ENWebArchiveDataMIMEType;

typedef void (^ENNotePopulateFromWebViewCompletionHandler)(ENNote * note);
typedef void (^ENNoteGenerateWebArchiveDataCompletionHandler)(NSData * data);

/**
 *  This class represents a fully specified note. (It does not "point" to any particular
 *  note in the Evernote service.) An ENNote used to upload to the service, and dowloading
 *  a note from the service will give you one.
 */
@interface ENNote : NSObject

/**
 *  The title of the note.
 */
@property (nonatomic, copy) NSString * title;

/**
 *  The content of the note.
 */
@property (nonatomic, strong) ENNoteContent * content;

/**
 *  An array of strings containing tag names to attach to an uploaded note. If a tag name already
 *  exists on upload, it will be used; if the tag name doesn't exist, it will be created.
 *  N.B. This array is generally NOT populated on note download, even if the note that was downloaded
 *  is tagged on the service.
 */
@property (nonatomic, copy) NSArray * tagNames;

/**
 *  A flag indicating whether this note is a "reminder".
 */
@property (nonatomic, assign) BOOL isReminder;

/**
 *  The array of resource objects current attached to this note.
 *
 *  @return An array of ENResources.
 */
- (NSArray *)resources;

/**
 *  Add a resource obejct to this note.
 *
 *  @param resource A fully-specified ENResource.
 */
- (void)addResource:(ENResource *)resource;

/**
 *  Removes all resources currently attached.
 */
- (void)removeAllResources;

/**
 *  A note can be rendered for the user within a web view. This method generates a web archive from the
 *  receiver's content. This archive is a single data object that can be given to a UIWebView's -loadData:...
 *  method, using the MIME type defined as ENWebArchiveDataMIMEType. This method is asynchronous, but does
 *  not operate using any remote resources; it can generally be safely used without e.g. a background 
 *  thread/progress indicator.
 *
 *  @param completion A block to receive the web archive data.
 */
- (void)generateWebArchiveData:(ENNoteGenerateWebArchiveDataCompletionHandler)completion;

@end
