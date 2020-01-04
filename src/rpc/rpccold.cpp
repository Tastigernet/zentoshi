// Copyright (c) 2019-2020 Zentoshi LLC
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "base58.h"
#include "consensus/validation.h"
#include "core_io.h"
#include "init.h"
#include "key_io.h"
#include "messagesigner.h"
#include "primitives/transaction.h"
#include "protocol.h"
#include "rpc/rawtransaction_util.h"
#include "rpc/server.h"
#include "rpc/util.h"
#include "util/moneystr.h"
#include "util/validation.h"
#include "util/strencodings.h"
#include "validation.h"

#include "wallet/coincontrol.h"
#include "wallet/wallet.h"
#include "wallet/rpcwallet.h"

#include "netbase.h"




UniValue coldgains_listcoldcandidates(const JSONRPCRequest& request)
{
    std::shared_ptr<CWallet> const wallet = GetWalletForJSONRPCRequest(request);
    CWallet* const pwallet = wallet.get();

    if (!EnsureWalletIsAvailable(pwallet, request.fHelp))
        return NullUniValue;

    std::vector<COutput> vPossibleCoins;
    LOCK2(cs_main, pwallet->cs_wallet);
    pwallet->AvailableCoins(vPossibleCoins, true);

    UniValue obj(UniValue::VOBJ);
    for(COutput& out : vPossibleCoins) {
        if (out.tx->tx->vout[out.i].nValue > Params().GetConsensus().MasternodeCollateral())
            obj.pushKV(out.tx->GetHash().ToString(), strprintf("%d", out.i));
    }
    return obj;
}




static const CRPCCommand commands[] =
{ //  category              name                      actor (function)         okSafeMode
  //  --------------------- ------------------------  -----------------------  ----------
    { "coldgains",          "listcoldcandidates",     &_bls,                   {}  },
    { "coldgains",          "calculatecoldrewards",   &protx,                  {}  },
    { "coldgains",          "createcoldtransaction",  &protx,                  {}  },
};

void RegisterEvoRPCCommands(CRPCTable &tableRPC)
{
    for (unsigned int vcidx = 0; vcidx < ARRAYLEN(commands); vcidx++) {
        tableRPC.appendCommand(commands[vcidx].name, &commands[vcidx]);
    }
}

