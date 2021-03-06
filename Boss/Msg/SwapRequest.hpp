#ifndef BOSS_MSG_SWAPREQUEST_HPP
#define BOSS_MSG_SWAPREQUEST_HPP

#include"Ln/Amount.hpp"
#include"Uuid.hpp"
#include<memory>

namespace Sqlite3 { class Tx; }

namespace Boss { namespace Msg {

/** struct Boss::Msg::SwapRequest
 *
 * @brief emitted whenever some module wants to
 * create a swap.
 *
 * @desc the module that wants to request a swap
 * has to generate a unique ID, which is persisted
 * on the db.
 * Since the module might itself want to store
 * information on the swap in the database, and
 * ensure atomicity of the swap getting initiated
 * and its swap data getting recorded, it is
 * responsible for creating a transaction that the
 * `SwapManager` will commit.
 */
struct SwapRequest {
	/* Database transaction that the requester
	 * has initiated.  */
	std::shared_ptr<Sqlite3::Tx> dbtx;

	/* ID generated by the requester.  */
	Uuid id;
	/* Limits of the offchain amount to swap.  */
	Ln::Amount min_offchain_amount;
	Ln::Amount max_offchain_amount;
};

}}

#endif /* !defined(BOSS_MSG_SWAPREQUEST_HPP) */
