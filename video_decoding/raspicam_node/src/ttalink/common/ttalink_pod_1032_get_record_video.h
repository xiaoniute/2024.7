#pragma once
// MESSAGE POD_1032_GET_RECORD_VIDEO PACKING

#define TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO 11032

TTAPACKED(
typedef struct __ttalink_pod_1032_get_record_video_t {
 uint8_t ack; /*<  .*/
 uint8_t ack_state; /*<  Video action
											0 :  Not in recording state;
											1 :  Records;*/
 uint16_t ack_run_time; /*<  Duration of the currently recorded video, in seconds.*/
}) ttalink_pod_1032_get_record_video_t;

#define TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN 4
#define TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN 4
#define TTALINK_MSG_ID_11032_LEN 4
#define TTALINK_MSG_ID_11032_MIN_LEN 4

#define TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC 228
#define TTALINK_MSG_ID_11032_CRC 228



#if TTALINK_COMMAND_24BIT
#define TTALINK_MESSAGE_INFO_POD_1032_GET_RECORD_VIDEO { \
    11032, \
    "POD_1032_GET_RECORD_VIDEO", \
    3, \
    {  { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 0, offsetof(ttalink_pod_1032_get_record_video_t, ack) }, \
         { "ack_state", NULL, TTALINK_TYPE_UINT8_T, 0, 1, offsetof(ttalink_pod_1032_get_record_video_t, ack_state) }, \
         { "ack_run_time", NULL, TTALINK_TYPE_UINT16_T, 0, 2, offsetof(ttalink_pod_1032_get_record_video_t, ack_run_time) }, \
         } \
}
#else
#define TTALINK_MESSAGE_INFO_POD_1032_GET_RECORD_VIDEO { \
    "POD_1032_GET_RECORD_VIDEO", \
    3, \
    {  { "ack", NULL, TTALINK_TYPE_UINT8_T, 0, 0, offsetof(ttalink_pod_1032_get_record_video_t, ack) }, \
         { "ack_state", NULL, TTALINK_TYPE_UINT8_T, 0, 1, offsetof(ttalink_pod_1032_get_record_video_t, ack_state) }, \
         { "ack_run_time", NULL, TTALINK_TYPE_UINT16_T, 0, 2, offsetof(ttalink_pod_1032_get_record_video_t, ack_run_time) }, \
         } \
}
#endif


static inline uint16_t _ttalink_pod_1032_get_record_video_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t ack, uint8_t ack_state, uint16_t ack_run_time, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN];
    _tta_put_uint8_t(buf, 0, ack);
    _tta_put_uint8_t(buf, 1, ack_state);
    _tta_put_uint16_t(buf, 2, ack_run_time);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN);
#else
    ttalink_pod_1032_get_record_video_t packet;
    packet.ack = ack;
    packet.ack_state = ack_state;
    packet.ack_run_time = ack_run_time;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO;
    return ttalink_finalize_message(msg, dst_addr, src_addr, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
}

/**
 * @brief Pack a pod_1032_get_record_video message
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1032_get_record_video_pack(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    return _ttalink_pod_1032_get_record_video_pack(dst_addr, src_addr, msg,  ack, ack_state, ack_run_time, false);
}

/**
 * @brief Pack a pod_1032_get_record_video message, no crc
 * @param dst_addr 
 * @param src_addr
 * @param msg The TTAlink message to compress the data into
 *
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1032_get_record_video_pack_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg,
                               uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    return _ttalink_pod_1032_get_record_video_pack(dst_addr, src_addr, msg,  ack, ack_state, ack_run_time, true);
}


static inline uint16_t _ttalink_pod_1032_get_record_video_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t ack,uint8_t ack_state,uint16_t ack_run_time, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN];
    _tta_put_uint8_t(buf, 0, ack);
    _tta_put_uint8_t(buf, 1, ack_state);
    _tta_put_uint16_t(buf, 2, ack_run_time);

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), buf, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN);
#else
    ttalink_pod_1032_get_record_video_t packet;
    packet.ack = ack;
    packet.ack_state = ack_state;
    packet.ack_run_time = ack_run_time;

        memcpy(_TTA_PAYLOAD_NON_CONST(msg), &packet, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN);
#endif

    msg->msgid = TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO;
    return ttalink_finalize_message_chan(msg, dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
}

/**
 * @brief Pack a pod_1032_get_record_video message on a channel
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1032_get_record_video_pack_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t ack,uint8_t ack_state,uint16_t ack_run_time)
{
    return _ttalink_pod_1032_get_record_video_pack_chan(dst_addr, src_addr, chan, msg,  ack, ack_state, ack_run_time, false);
}

/**
 * @brief Pack a pod_1032_get_record_video message on a channel, no crc
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t ttalink_pod_1032_get_record_video_pack_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan,
                               ttalink_message_t* msg,
                                   uint8_t ack,uint8_t ack_state,uint16_t ack_run_time)
{
    return _ttalink_pod_1032_get_record_video_pack_chan(dst_addr, src_addr, chan, msg,  ack, ack_state, ack_run_time, true);
}


static inline uint16_t _ttalink_pod_1032_get_record_video_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video, bool nocrc)
{
    if(nocrc){
        return ttalink_pod_1032_get_record_video_pack_nocrc(dst_addr, src_addr, msg, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }else{
        return ttalink_pod_1032_get_record_video_pack(dst_addr, src_addr, msg, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }
    
}

/**
 * @brief Encode a pod_1032_get_record_video struct
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param pod_1032_get_record_video C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1032_get_record_video_encode(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    return _ttalink_pod_1032_get_record_video_encode(dst_addr, src_addr, msg, pod_1032_get_record_video, false);
}

/**
 * @brief Encode a pod_1032_get_record_video struct, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param msg The TTAlink message to compress the data into
 * @param pod_1032_get_record_video C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1032_get_record_video_encode_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    return _ttalink_pod_1032_get_record_video_encode(dst_addr, src_addr, msg, pod_1032_get_record_video, true);
}


static inline uint16_t _ttalink_pod_1032_get_record_video_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video, bool nocrc)
{
    if(nocrc){
        return ttalink_pod_1032_get_record_video_pack_chan_nocrc(dst_addr, src_addr, chan, msg, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }else{
        return ttalink_pod_1032_get_record_video_pack_chan(dst_addr, src_addr, chan, msg, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }
}

/**
 * @brief Encode a pod_1032_get_record_video struct on a channel
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param pod_1032_get_record_video C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1032_get_record_video_encode_chan(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    return _ttalink_pod_1032_get_record_video_encode_chan(dst_addr, src_addr, chan, msg, pod_1032_get_record_video, false);
}

/**
 * @brief Encode a pod_1032_get_record_video struct on a channel, no crc
 *
 * @param dst_addr ID of this system
 * @param src_addr ID of this component (e.g. 200 for IMU)
 * @param chan The TTAlink channel this message will be sent over
 * @param msg The TTAlink message to compress the data into
 * @param pod_1032_get_record_video C-struct to read the message contents from
 */
static inline uint16_t ttalink_pod_1032_get_record_video_encode_chan_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, ttalink_message_t* msg, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    return _ttalink_pod_1032_get_record_video_encode_chan(dst_addr, src_addr, chan, msg, pod_1032_get_record_video, true);
}


#ifdef TTALINK_USE_CONVENIENCE_FUNCTIONS

static inline void _ttalink_pod_1032_get_record_video_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t ack, uint8_t ack_state, uint16_t ack_run_time, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char buf[TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN];
    _tta_put_uint8_t(buf, 0, ack);
    _tta_put_uint8_t(buf, 1, ack_state);
    _tta_put_uint16_t(buf, 2, ack_run_time);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO, buf, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
#else
    ttalink_pod_1032_get_record_video_t packet;
    packet.ack = ack;
    packet.ack_state = ack_state;
    packet.ack_run_time = ack_run_time;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO, (const char *)&packet, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
#endif
}

/**
 * @brief Send a pod_1032_get_record_video message
 * @param chan TTAlink channel to send the message
 *
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 */
static inline void ttalink_pod_1032_get_record_video_send(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    _ttalink_pod_1032_get_record_video_send(dst_addr, src_addr, chan, ack, ack_state, ack_run_time, false);
}

/**
 * @brief Send a pod_1032_get_record_video message, no crc
 * @param chan TTAlink channel to send the message
 *
 * @param ack  .
 * @param ack_state  Video action
											0 :  Not in recording state;
											1 :  Records;
 * @param ack_run_time  Duration of the currently recorded video, in seconds.
 */
static inline void ttalink_pod_1032_get_record_video_send_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    _ttalink_pod_1032_get_record_video_send(dst_addr, src_addr, chan, ack, ack_state, ack_run_time, true);
}


static inline void _ttalink_pod_1032_get_record_video_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    if(nocrc){
        ttalink_pod_1032_get_record_video_send_nocrc(dst_addr, src_addr, chan, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }else{
        ttalink_pod_1032_get_record_video_send(dst_addr, src_addr, chan, pod_1032_get_record_video->ack, pod_1032_get_record_video->ack_state, pod_1032_get_record_video->ack_run_time);
    }
#else
    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO, (const char *)pod_1032_get_record_video, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
#endif
}

/**
 * @brief Send a pod_1032_get_record_video message
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_pod_1032_get_record_video_send_struct(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    _ttalink_pod_1032_get_record_video_send_struct(dst_addr, src_addr, chan, pod_1032_get_record_video, false);
}

/**
 * @brief Send a pod_1032_get_record_video message, no crc
 * @param chan TTAlink channel to send the message
 * @param struct The TTAlink struct to serialize
 */
static inline void ttalink_pod_1032_get_record_video_send_struct_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_channel_t chan, const ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
    _ttalink_pod_1032_get_record_video_send_struct(dst_addr, src_addr, chan, pod_1032_get_record_video, true);
}

#if TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN <= TTALINK_MAX_PAYLOAD_LEN
static inline void _ttalink_pod_1032_get_record_video_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t ack, uint8_t ack_state, uint16_t ack_run_time, bool nocrc)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _tta_put_uint8_t(buf, 0, ack);
    _tta_put_uint8_t(buf, 1, ack_state);
    _tta_put_uint16_t(buf, 2, ack_run_time);

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO, buf, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
#else
    ttalink_pod_1032_get_record_video_t *packet = (ttalink_pod_1032_get_record_video_t *)msgbuf;
    packet->ack = ack;
    packet->ack_state = ack_state;
    packet->ack_run_time = ack_run_time;

    _tta_finalize_message_chan_send(dst_addr, src_addr, chan, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO, (const char *)packet, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_MIN_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_CRC, nocrc);
#endif
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void ttalink_pod_1032_get_record_video_send_buf(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    _ttalink_pod_1032_get_record_video_send_buf(dst_addr, src_addr, msgbuf, chan, ack, ack_state, ack_run_time, false);
}

/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  ttalink_message_t which is the size of a full ttalink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage, no crc.
 */
static inline void ttalink_pod_1032_get_record_video_send_buf_nocrc(uint8_t dst_addr, uint8_t src_addr, ttalink_message_t *msgbuf, ttalink_channel_t chan,  uint8_t ack, uint8_t ack_state, uint16_t ack_run_time)
{
    _ttalink_pod_1032_get_record_video_send_buf(dst_addr, src_addr, msgbuf, chan, ack, ack_state, ack_run_time, true);
}
#endif

#endif

// MESSAGE POD_1032_GET_RECORD_VIDEO UNPACKING


/**
 * @brief Get field ack from pod_1032_get_record_video message
 *
 * @return  .
 */
static inline uint8_t ttalink_pod_1032_get_record_video_get_ack(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field ack_state from pod_1032_get_record_video message
 *
 * @return  Video action
											0 :  Not in recording state;
											1 :  Records;
 */
static inline uint8_t ttalink_pod_1032_get_record_video_get_ack_state(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field ack_run_time from pod_1032_get_record_video message
 *
 * @return  Duration of the currently recorded video, in seconds.
 */
static inline uint16_t ttalink_pod_1032_get_record_video_get_ack_run_time(const ttalink_message_t* msg)
{
    return _TTA_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a pod_1032_get_record_video message into a struct
 *
 * @param msg The message to decode
 * @param pod_1032_get_record_video C-struct to decode the message contents into
 */
static inline void ttalink_pod_1032_get_record_video_decode(const ttalink_message_t* msg, ttalink_pod_1032_get_record_video_t* pod_1032_get_record_video)
{
#if TTALINK_NEED_BYTE_SWAP || !TTALINK_ALIGNED_FIELDS
    pod_1032_get_record_video->ack = ttalink_pod_1032_get_record_video_get_ack(msg);
    pod_1032_get_record_video->ack_state = ttalink_pod_1032_get_record_video_get_ack_state(msg);
    pod_1032_get_record_video->ack_run_time = ttalink_pod_1032_get_record_video_get_ack_run_time(msg);
#else
        uint8_t len = msg->len < TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN? msg->len : TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN;
        memset(pod_1032_get_record_video, 0, TTALINK_MSG_ID_POD_1032_GET_RECORD_VIDEO_LEN);
    memcpy(pod_1032_get_record_video, _TTA_PAYLOAD(msg), len);
#endif
}
