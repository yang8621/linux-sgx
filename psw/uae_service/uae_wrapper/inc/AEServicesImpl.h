/*
 * Copyright (C) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef __AE_SERVICES_IMPL_H__
#define __AE_SERVICES_IMPL_H__

#include <AEServicesProvider.h>
#include <AEInternalServicesProvider.h>
#include <AEInternalServices.h>

class ITransporter;

class AEServicesImpl : public AEInternalServices{
    public:
        ~AEServicesImpl();

       QuoteInfo* GetQuote(const Report* report, const uint32_t quoteType, const SPID* spid, const Nonce* nonce, 
                                const SignatureRevocationList* sig_rl, const uint32_t bufSize, const bool qe_report, uint32_t timeout_msec=0); 

        AttestationInformation* InitQuote(uint32_t timeout_msec=0);

        LaunchToken* GetLaunchToken(EnclaveMeasurement *mr_enclave,
                                      Signature          *mr_signer,
                                      SEAttributes       *se_attributes,
                                        uint32_t timeout_msec=0);

        CreateSessionInformation* CreateSession(uint32_t dhMsg1Size, uint32_t timeout = 0);

        PSEMessage* InvokeService(PSEMessage* targetServiceMessage, uint32_t pseResponseSize, uint32_t timeout = 0);

        PlainData*  ExchangeReport(uint32_t sessionId, PlainData* dhMsg, uint32_t pseResponseSize, uint32_t timeout = 0);

        PlainData* CloseSession(uint32_t sessionId, uint32_t timeout = 0);
        
        PsCap* GetPsCap(uint32_t timeout_msec=0);

        AttestationStatus* ReportAttestationError(const PlatformInfo* platformInfo, uint32_t attestation_error_code, uint32_t updateInfoLength,uint32_t timeout_msec=0) ;
        
        friend AEServices* AEServicesProvider::GetServicesProvider();
        friend AEInternalServices* AEInternalServicesProvider::GetInternalServicesProvider();

    protected:
        AEServicesImpl(const char* socketbase);
        static bool     mBoundToService;
        ITransporter*   mTransporter;       //the internal interface to the AESM

    private:
        AEServicesImpl& operator=(const AEServicesImpl&);
        AEServicesImpl(const AEServicesImpl&);
};

#endif
