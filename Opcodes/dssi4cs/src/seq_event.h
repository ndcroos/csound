/**
 * \file include/seq_event.h
 * \brief Application interface library for the ALSA driver
 * \author Jaroslav Kysela <perex@suse.cz>
 * \author Abramo Bagnara <abramo@alsa-project.org>
 * \author Takashi Iwai <tiwai@suse.de>
 * \date 1998-2001
 *
 * Application interface library for the ALSA driver
 */
/*
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as
 *   published by the Free Software Foundation; either version 2.1 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __ALSA_SEQ_EVENT_H
#define __ALSA_SEQ_EVENT_H

/**
 *  \defgroup SeqEvents Sequencer Event Definitions
 *  Sequencer Event Definitions
 *  \ingroup Sequencer
 *  \{
 */

/**
 * Sequencer event data type
 */
typedef unsigned char snd_seq_event_type_t;

/** Sequencer event type */
enum snd_seq_event_type {
        /** system status; event data type = #snd_seq_result_t */
        SND_SEQ_EVENT_SYSTEM = 0,
        /** returned result status; event data type = #snd_seq_result_t */
        SND_SEQ_EVENT_RESULT,

        /** note on and off with duration; event data type = #snd_seq_ev_note_t */
        SND_SEQ_EVENT_NOTE = 5,
        /** note on; event data type = #snd_seq_ev_note_t */
        SND_SEQ_EVENT_NOTEON,
        /** note off; event data type = #snd_seq_ev_note_t */
        SND_SEQ_EVENT_NOTEOFF,
        /** key pressure change (aftertouch);
            event data type = #snd_seq_ev_note_t */
        SND_SEQ_EVENT_KEYPRESS,

        /** controller; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_CONTROLLER = 10,
        /** program change; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_PGMCHANGE,
        /** channel pressure; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_CHANPRESS,
        /** pitchwheel; event data type = #snd_seq_ev_ctrl_t;
            data is from -8192 to 8191) */
        SND_SEQ_EVENT_PITCHBEND,
        /** 14 bit controller value; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_CONTROL14,
        /** 14 bit NRPN;  event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_NONREGPARAM,
        /** 14 bit RPN; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_REGPARAM,

        /** SPP with LSB and MSB values; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_SONGPOS = 20,
        /** Song Select with song ID number; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_SONGSEL,
        /** midi time code quarter frame; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_QFRAME,
        /** SMF Time Signature event; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_TIMESIGN,
        /** SMF Key Signature event; event data type = #snd_seq_ev_ctrl_t */
        SND_SEQ_EVENT_KEYSIGN,

        /** MIDI Real Time Start message;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_START = 30,
        /** MIDI Real Time Continue message;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_CONTINUE,
        /** MIDI Real Time Stop message;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_STOP,
        /** Set tick queue position;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_SETPOS_TICK,
        /** Set real-time queue position;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_SETPOS_TIME,
        /** (SMF) Tempo event; event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_TEMPO,
        /** MIDI Real Time Clock message;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_CLOCK,
        /** MIDI Real Time Tick message;
            event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_TICK,
        /** Queue timer skew; event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_QUEUE_SKEW,
        /** Sync position changed; event data type = #snd_seq_ev_queue_control_t */
        SND_SEQ_EVENT_SYNC_POS,

        /** Tune request; event data type = none */
        SND_SEQ_EVENT_TUNE_REQUEST = 40,
        /** Reset to power-on state; event data type = none */
        SND_SEQ_EVENT_RESET,
        /** Active sensing event; event data type = none */
        SND_SEQ_EVENT_SENSING,

        /** Echo-back event; event data type = any type */
        SND_SEQ_EVENT_ECHO = 50,
        /** OSS emulation raw event; event data type = any type */
        SND_SEQ_EVENT_OSS,

        /** New client has connected; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_CLIENT_START = 60,
        /** Client has left the system; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_CLIENT_EXIT,
        /** Client status/info has changed; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_CLIENT_CHANGE,
        /** New port was created; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_PORT_START,
        /** Port was deleted from system; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_PORT_EXIT,
        /** Port status/info has changed; event data type = #snd_seq_addr_t */
        SND_SEQ_EVENT_PORT_CHANGE,

        /** Ports connected; event data type = #snd_seq_connect_t */
        SND_SEQ_EVENT_PORT_SUBSCRIBED,
        /** Ports disconnected; event data type = #snd_seq_connect_t */
        SND_SEQ_EVENT_PORT_UNSUBSCRIBED,

        /** Sample select; event data type = #snd_seq_ev_sample_control_t */
        SND_SEQ_EVENT_SAMPLE = 70,
        /** Sample cluster select; event data type = #snd_seq_ev_sample_control_t */
        SND_SEQ_EVENT_SAMPLE_CLUSTER,
        /** voice start */
        SND_SEQ_EVENT_SAMPLE_START,
        /** voice stop */
        SND_SEQ_EVENT_SAMPLE_STOP,
        /** playback frequency */
        SND_SEQ_EVENT_SAMPLE_FREQ,
        /** volume and balance */
        SND_SEQ_EVENT_SAMPLE_VOLUME,
        /** sample loop */
        SND_SEQ_EVENT_SAMPLE_LOOP,
        /** sample position */
        SND_SEQ_EVENT_SAMPLE_POSITION,
        /** private (hardware dependent) event */
        SND_SEQ_EVENT_SAMPLE_PRIVATE1,

        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR0 = 90,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR1,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR2,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR3,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR4,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR5,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR6,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR7,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR8,
        /** user-defined event; event data type = any (fixed size) */
        SND_SEQ_EVENT_USR9,

        /** begin of instrument management */
        SND_SEQ_EVENT_INSTR_BEGIN = 100,
        /** end of instrument management */
        SND_SEQ_EVENT_INSTR_END,
        /** query instrument interface info */
        SND_SEQ_EVENT_INSTR_INFO,
        /** result of instrument interface info */
        SND_SEQ_EVENT_INSTR_INFO_RESULT,
        /** query instrument format info */
        SND_SEQ_EVENT_INSTR_FINFO,
        /** result of instrument format info */
        SND_SEQ_EVENT_INSTR_FINFO_RESULT,
        /** reset instrument instrument memory */
        SND_SEQ_EVENT_INSTR_RESET,
        /** get instrument interface status */
        SND_SEQ_EVENT_INSTR_STATUS,
        /** result of instrument interface status */
        SND_SEQ_EVENT_INSTR_STATUS_RESULT,
        /** put an instrument to port */
        SND_SEQ_EVENT_INSTR_PUT,
        /** get an instrument from port */
        SND_SEQ_EVENT_INSTR_GET,
        /** result of instrument query */
        SND_SEQ_EVENT_INSTR_GET_RESULT,
        /** free instrument(s) */
        SND_SEQ_EVENT_INSTR_FREE,
        /** get instrument list */
        SND_SEQ_EVENT_INSTR_LIST,
        /** result of instrument list */
        SND_SEQ_EVENT_INSTR_LIST_RESULT,
        /** set cluster parameters */
        SND_SEQ_EVENT_INSTR_CLUSTER,
        /** get cluster parameters */
        SND_SEQ_EVENT_INSTR_CLUSTER_GET,
        /** result of cluster parameters */
        SND_SEQ_EVENT_INSTR_CLUSTER_RESULT,
        /** instrument change */
        SND_SEQ_EVENT_INSTR_CHANGE,

        /** system exclusive data (variable length);
            event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_SYSEX = 130,
        /** error event;  event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_BOUNCE,
        /** reserved for user apps;  event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_USR_VAR0 = 135,
        /** reserved for user apps; event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_USR_VAR1,
        /** reserved for user apps; event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_USR_VAR2,
        /** reserved for user apps; event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_USR_VAR3,
        /** reserved for user apps; event data type = #snd_seq_ev_ext_t */
        SND_SEQ_EVENT_USR_VAR4,

        /** NOP; ignored in any case */
        SND_SEQ_EVENT_NONE = 255
};

/** Sequencer event address */
typedef struct snd_seq_addr {
        unsigned char client;   /**< Client id */
        unsigned char port;     /**< Port id */
} snd_seq_addr_t;

/** Connection (subscription) between ports */
typedef struct snd_seq_connect {
        snd_seq_addr_t sender;  /**< sender address */
        snd_seq_addr_t dest;    /**< destination address */
} snd_seq_connect_t;

/** Real-time data record */
typedef struct snd_seq_real_time {
        unsigned int tv_sec;            /**< seconds */
        unsigned int tv_nsec;           /**< nanoseconds */
} snd_seq_real_time_t;

/** (MIDI) Tick-time data record */
typedef unsigned int snd_seq_tick_time_t;

/** unioned time stamp */
typedef union snd_seq_timestamp {
        snd_seq_tick_time_t tick;       /**< tick-time */
        struct snd_seq_real_time time;  /**< real-time */
} snd_seq_timestamp_t;

/**
 * Event mode flags
 *
 * NOTE: only 8 bits available!
 */
#define SND_SEQ_TIME_STAMP_TICK         (0<<0)  /**< timestamp in clock ticks */
#define SND_SEQ_TIME_STAMP_REAL         (1<<0)  /**< timestamp in real time */
#define SND_SEQ_TIME_STAMP_MASK         (1<<0)  /**< mask for timestamp bits */

#define SND_SEQ_TIME_MODE_ABS           (0<<1)  /**< absolute timestamp */
#define SND_SEQ_TIME_MODE_REL           (1<<1)  /**< relative to current time */
#define SND_SEQ_TIME_MODE_MASK          (1<<1)  /**< mask for time mode bits */

#define SND_SEQ_EVENT_LENGTH_FIXED      (0<<2)  /**< fixed event size */
#define SND_SEQ_EVENT_LENGTH_VARIABLE   (1<<2)  /**< variable event size */
#define SND_SEQ_EVENT_LENGTH_VARUSR     (2<<2)  /**< variable event size -
                                                   user memory space */
#define SND_SEQ_EVENT_LENGTH_MASK       (3<<2)  /**< mask for event length bits */

#define SND_SEQ_PRIORITY_NORMAL         (0<<4)  /**< normal priority */
#define SND_SEQ_PRIORITY_HIGH           (1<<4)  /**< event should be processed
                                                   before others */
#define SND_SEQ_PRIORITY_MASK           (1<<4)  /**< mask for priority bits */

/** Note event */
typedef struct snd_seq_ev_note {
        unsigned char channel;          /**< channel number */
        unsigned char note;             /**< note */
        unsigned char velocity;         /**< velocity */
        unsigned char off_velocity;     /**< note-off velocity;
                                           only for #SND_SEQ_EVENT_NOTE */
        unsigned int duration;          /**< duration until note-off;
                                           only for #SND_SEQ_EVENT_NOTE */
} snd_seq_ev_note_t;

/** Controller event */
typedef struct snd_seq_ev_ctrl {
        unsigned char channel;          /**< channel number */
        unsigned char unused[3];        /**< reserved */
        unsigned int param;             /**< control parameter */
        signed int value;               /**< control value */
} snd_seq_ev_ctrl_t;

/** generic set of bytes (12x8 bit) */
typedef struct snd_seq_ev_raw8 {
        unsigned char d[12];            /**< 8 bit value */
} snd_seq_ev_raw8_t;

/** generic set of integers (3x32 bit) */
typedef struct snd_seq_ev_raw32 {
        unsigned int d[3];              /**< 32 bit value */
} snd_seq_ev_raw32_t;

/** external stored data */
typedef struct snd_seq_ev_ext {
        unsigned int len;       /**< length of data */
        void *ptr;              /**< pointer to data (note: can be 64-bit) */
} __attribute__((packed)) snd_seq_ev_ext_t;

/** Instrument cluster type */
typedef unsigned int snd_seq_instr_cluster_t;

/** Instrument type */
typedef struct snd_seq_instr {
        snd_seq_instr_cluster_t cluster;        /**< cluster id */
        unsigned int std;       /**< instrument standard id; the upper
                                   byte means a private instrument
                                   (owner - client id) */
        unsigned short bank;    /**< instrument bank id */
        unsigned short prg;     /**< instrument program id */
} snd_seq_instr_t;

/** sample number */
typedef struct snd_seq_ev_sample {
        unsigned int std;       /**< sample standard id */
        unsigned short bank;    /**< sample bank id */
        unsigned short prg;     /**< sample program id */
} snd_seq_ev_sample_t;

/** sample cluster */
typedef struct snd_seq_ev_cluster {
        snd_seq_instr_cluster_t cluster;        /**< cluster id */
} snd_seq_ev_cluster_t;

/** sample position */
typedef unsigned int snd_seq_position_t; /**< playback position (in samples) * 16 */

/** sample stop mode */
typedef enum snd_seq_stop_mode {
  SND_SEQ_SAMPLE_STOP_IMMEDIATELY = 0,    /**< terminate playing immediately */
  SND_SEQ_SAMPLE_STOP_VENVELOPE = 1,      /**< finish volume envelope */
  SND_SEQ_SAMPLE_STOP_LOOP = 2            /**< terminate loop and finish wave */
} snd_seq_stop_mode_t;

/** sample frequency */
typedef int snd_seq_frequency_t; /**< playback frequency in HZ * 16 */

/** sample volume control; if any value is set to -1 == do not change */
typedef struct snd_seq_ev_volume {
        signed short volume;    /**< range: 0-16383 */
        signed short lr;        /**< left-right balance; range: 0-16383 */
        signed short fr;        /**< front-rear balance; range: 0-16383 */
        signed short du;        /**< down-up balance; range: 0-16383 */
} snd_seq_ev_volume_t;

/** simple loop redefinition */
typedef struct snd_seq_ev_loop {
        unsigned int start;     /**< loop start (in samples) * 16 */
        unsigned int end;       /**< loop end (in samples) * 16 */
} snd_seq_ev_loop_t;

/** Sample control events */
typedef struct snd_seq_ev_sample_control {
        unsigned char channel;          /**< channel */
        unsigned char unused[3];        /**< reserved */
        union {
                snd_seq_ev_sample_t sample;     /**< sample number */
                snd_seq_ev_cluster_t cluster;   /**< cluster number */
                snd_seq_position_t position;    /**< position */
                snd_seq_stop_mode_t stop_mode;  /**< stop mode */
                snd_seq_frequency_t frequency;  /**< frequency */
                snd_seq_ev_volume_t volume;     /**< volume */
                snd_seq_ev_loop_t loop;         /**< loop control */
                unsigned char raw8[8];          /**< raw 8-bit */
        } param;                /**< control parameters */
} snd_seq_ev_sample_control_t;

/** INSTR_BEGIN event */
typedef struct snd_seq_ev_instr_begin {
        int timeout;            /**< zero = forever, otherwise timeout in ms */
} snd_seq_ev_instr_begin_t;

/** Result events */
typedef struct snd_seq_result {
        int event;              /**< processed event type */
        int result;             /**< status */
} snd_seq_result_t;

/** Queue skew values */
typedef struct snd_seq_queue_skew {
        unsigned int value;     /**< skew value */
        unsigned int base;      /**< skew base */
} snd_seq_queue_skew_t;

/** queue timer control */
typedef struct snd_seq_ev_queue_control {
        unsigned char queue;                    /**< affected queue */
        unsigned char unused[3];                /**< reserved */
        union {
                signed int value;               /**< affected value (e.g. tempo) */
                snd_seq_timestamp_t time;       /**< time */
                unsigned int position;          /**< sync position */
                snd_seq_queue_skew_t skew;      /**< queue skew */
                unsigned int d32[2];            /**< any data */
                unsigned char d8[8];            /**< any data */
        } param;                                /**< data value union */
} snd_seq_ev_queue_control_t;

/** Sequencer event */
typedef struct snd_seq_event {
        snd_seq_event_type_t type;      /**< event type */
        unsigned char flags;            /**< event flags */
        unsigned char tag;              /**< tag */

        unsigned char queue;            /**< schedule queue */
        snd_seq_timestamp_t time;       /**< schedule time */

        snd_seq_addr_t source;          /**< source address */
        snd_seq_addr_t dest;            /**< destination address */

        union {
                snd_seq_ev_note_t note;         /**< note information */
                snd_seq_ev_ctrl_t control;      /**< MIDI control information */
                snd_seq_ev_raw8_t raw8;         /**< raw8 data */
                snd_seq_ev_raw32_t raw32;       /**< raw32 data */
                snd_seq_ev_ext_t ext;           /**< external data */
                snd_seq_ev_queue_control_t queue; /**< queue control */
                snd_seq_timestamp_t time;       /**< timestamp */
                snd_seq_addr_t addr;            /**< address */
                snd_seq_connect_t connect;      /**< connect information */
                snd_seq_result_t result;        /**< operation result code */
                snd_seq_ev_instr_begin_t instr_begin; /**< instrument */
                snd_seq_ev_sample_control_t sample; /**< sample control */
        } data;                         /**< event data... */
} snd_seq_event_t;

/** \} */

#endif /* __ALSA_SEQ_EVENT_H */

