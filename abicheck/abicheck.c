// ABI guard: the real Wi-Fi stack on this device is NOT built from the running
// 6.6.143 kernel tree.  /vendor/lib/modules/mac80211.ko was built by MediaTek
// (vermagic 6.6.58-android15-8-g33c1ba9ffede-4k) and loaded anyway, because the
// running kernel has CONFIG_MODVERSIONS=n and CONFIG_MODULE_FORCE_LOAD=y.
// Every wireless driver we build must therefore expose exactly the
// struct ieee80211_ops layout that this prebuilt mac80211 expects, otherwise
// ieee80211_alloc_hw_nm() reads NULL at ops->wake_tx_queue (0x2f0) and probe
// fails with -ENOMEM.
//
// The expected offsets below were extracted field-by-field from the .BTF
// section of the vendor mac80211.ko.  Compiling this file fails the CI build if
// any field ever drifts (e.g. someone disables CONFIG_NL80211_TESTMODE again).
#include <linux/module.h>
#include <linux/stddef.h>
#include <net/mac80211.h>

static int __init abicheck_init(void)
{
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tx) != 0x000);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, start) != 0x008);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, stop) != 0x010);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, suspend) != 0x018);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, resume) != 0x020);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_wakeup) != 0x028);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, add_interface) != 0x030);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, change_interface) != 0x038);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, remove_interface) != 0x040);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, config) != 0x048);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, bss_info_changed) != 0x050);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, vif_cfg_changed) != 0x058);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, link_info_changed) != 0x060);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, start_ap) != 0x068);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, stop_ap) != 0x070);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, prepare_multicast) != 0x078);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, configure_filter) != 0x080);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, config_iface_filter) != 0x088);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_tim) != 0x090);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_key) != 0x098);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, update_tkip_key) != 0x0a0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_rekey_data) != 0x0a8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_default_unicast_key) != 0x0b0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, hw_scan) != 0x0b8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, cancel_hw_scan) != 0x0c0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sched_scan_start) != 0x0c8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sched_scan_stop) != 0x0d0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sw_scan_start) != 0x0d8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sw_scan_complete) != 0x0e0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_stats) != 0x0e8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_key_seq) != 0x0f0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_frag_threshold) != 0x0f8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_rts_threshold) != 0x100);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_add) != 0x108);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_remove) != 0x110);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_notify) != 0x118);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_set_txpwr) != 0x120);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_state) != 0x128);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_pre_rcu_remove) != 0x130);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_rc_update) != 0x138);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_rate_tbl_update) != 0x140);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_statistics) != 0x148);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, conf_tx) != 0x150);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_tsf) != 0x158);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_tsf) != 0x160);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, offset_tsf) != 0x168);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, reset_tsf) != 0x170);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tx_last_beacon) != 0x178);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, ampdu_action) != 0x180);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_survey) != 0x188);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, rfkill_poll) != 0x190);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_coverage_class) != 0x198);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, testmode_cmd) != 0x1a0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, testmode_dump) != 0x1a8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, flush) != 0x1b0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, flush_sta) != 0x1b8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, channel_switch) != 0x1c0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_antenna) != 0x1c8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_antenna) != 0x1d0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, remain_on_channel) != 0x1d8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, cancel_remain_on_channel) != 0x1e0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_ringparam) != 0x1e8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_ringparam) != 0x1f0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tx_frames_pending) != 0x1f8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_bitrate_mask) != 0x200);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, event_callback) != 0x208);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, allow_buffered_frames) != 0x210);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, release_buffered_frames) != 0x218);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_et_sset_count) != 0x220);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_et_stats) != 0x228);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_et_strings) != 0x230);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, mgd_prepare_tx) != 0x238);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, mgd_complete_tx) != 0x240);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, mgd_protect_tdls_discover) != 0x248);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, add_chanctx) != 0x250);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, remove_chanctx) != 0x258);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, change_chanctx) != 0x260);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, assign_vif_chanctx) != 0x268);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, unassign_vif_chanctx) != 0x270);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, switch_vif_chanctx) != 0x278);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, reconfig_complete) != 0x280);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, ipv6_addr_change) != 0x288);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, channel_switch_beacon) != 0x290);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, pre_channel_switch) != 0x298);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, post_channel_switch) != 0x2a0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, abort_channel_switch) != 0x2a8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, channel_switch_rx_beacon) != 0x2b0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, join_ibss) != 0x2b8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, leave_ibss) != 0x2c0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_expected_throughput) != 0x2c8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_txpower) != 0x2d0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tdls_channel_switch) != 0x2d8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tdls_cancel_channel_switch) != 0x2e0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, tdls_recv_channel_switch) != 0x2e8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, wake_tx_queue) != 0x2f0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sync_rx_queues) != 0x2f8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, start_nan) != 0x300);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, stop_nan) != 0x308);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, nan_change_conf) != 0x310);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, add_nan_func) != 0x318);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, del_nan_func) != 0x320);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, can_aggregate_in_amsdu) != 0x328);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, get_ftm_responder_stats) != 0x330);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, start_pmsr) != 0x338);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, abort_pmsr) != 0x340);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_tid_config) != 0x348);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, reset_tid_config) != 0x350);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, update_vif_offload) != 0x358);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_set_4addr) != 0x360);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_sar_specs) != 0x368);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, sta_set_decap_offload) != 0x370);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, add_twt_setup) != 0x378);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, twt_teardown_request) != 0x380);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_radar_background) != 0x388);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, net_fill_forward_path) != 0x390);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, change_vif_links) != 0x398);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, change_sta_links) != 0x3a0);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, set_hw_timestamp) != 0x3a8);
BUILD_BUG_ON(offsetof(struct ieee80211_ops, net_setup_tc) != 0x3b0);
BUILD_BUG_ON(sizeof(struct ieee80211_ops) != 0x3b8);
	return 0;
}

static void __exit abicheck_exit(void) { }

module_init(abicheck_init);
module_exit(abicheck_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ieee80211_ops ABI guard for the vendor mac80211");
