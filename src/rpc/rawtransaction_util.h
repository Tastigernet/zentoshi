// Copyright (c) 2017-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RPC_RAWTRANSACTION_UTIL_H
#define BITCOIN_RPC_RAWTRANSACTION_UTIL_H

#include <rpc/server.h>

#include <univalue.h>

class CBasicKeyStore;
class UniValue;
struct CMutableTransaction;

namespace interfaces {
class Chain;
} // namespace interfaces

/** Sign a transaction with the given keystore and previous transactions */
UniValue SignTransaction(interfaces::Chain& chain, CMutableTransaction& mtx, const UniValue& prevTxs, CBasicKeyStore *keystore, bool tempKeystore, const UniValue& hashType);

/** Create a transaction from univalue parameters */
CMutableTransaction ConstructTransaction(const UniValue& inputs_in, const UniValue& outputs_in, const UniValue& locktime, bool rbf);

#ifdef ENABLE_WALLET
extern UniValue signrawtransaction(const JSONRPCRequest& request);
extern UniValue sendrawtransaction(const JSONRPCRequest& request);
#endif//ENABLE_WALLET

#endif // BITCOIN_RPC_RAWTRANSACTION_UTIL_H
