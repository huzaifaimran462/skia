/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef GrGLTextureRenderTarget_DEFINED
#define GrGLTextureRenderTarget_DEFINED

#include "GrGLTexture.h"
#include "GrGLRenderTarget.h"

class GrGLGpu;

#ifdef SK_BUILD_FOR_WIN
// Windows gives bogus warnings about inheriting asTexture/asRenderTarget via dominance.
#pragma warning(push)
#pragma warning(disable: 4250)
#endif

class GrGLTextureRenderTarget : public GrGLTexture, public GrGLRenderTarget {
public:
    // We're virtually derived from GrSurface (via both GrGLTexture and GrGLRenderTarget) so its
    // constructor must be explicitly called.
    GrGLTextureRenderTarget(GrGLGpu* gpu,
                            const GrSurfaceDesc& desc,
                            const GrGLTexture::IDDesc& texIDDesc,
                            const GrGLRenderTarget::IDDesc& rtIDDesc)
        : GrSurface(gpu, texIDDesc.fIsWrapped, desc)
        , GrGLTexture(gpu, desc, texIDDesc, GrGLTexture::kDerived)
        , GrGLRenderTarget(gpu, desc, rtIDDesc, GrGLRenderTarget::kDerived) {
        this->registerWithCache();
    }

protected:
    virtual void onAbandon() SK_OVERRIDE {
        GrGLRenderTarget::onAbandon();
        GrGLTexture::onAbandon();
    }

    virtual void onRelease() SK_OVERRIDE {
        GrGLRenderTarget::onRelease();
        GrGLTexture::onRelease();
    }

private:
    // GrGLRenderTarget accounts for the texture's memory and any MSAA renderbuffer's memory.
    virtual size_t onGpuMemorySize() const SK_OVERRIDE {
        return GrGLRenderTarget::onGpuMemorySize();
    }

};

#ifdef SK_BUILD_FOR_WIN
#pragma warning(pop)
#endif

#endif
