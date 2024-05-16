#pragma once
#include <cstdint>

namespace lora {
    /** Generates uniform random channels on a per-subband basis. */
    class RandomChannel {
        public:

            /** Picks a random channel from the given list of enabled channels. When all channels in the list
             * have been used, the pool will reset and a new batch of random channels can be randomly selected.
             *
             * This method takes a list of enabled channels to minimize disruption of changes within the
             * rest of the code base. The codebase calling this method has an array of enabled channels as a
             * mask instead of keeping track of a subband. Passing a subband as an argument would require
             * a substantial refactor to the rest of the codebase.
             *
             * @param enabledChannels list of channels to randomly select from.
             * @param nbEnabledChannels number of enabledChannels
             * @param channel updated with the randomly generated channel, value is valid only when this method
             *        returns true
             * @return false if any channels in the list are out of range or an error occured pulling a random
             *         channel
             */
            bool NextChannel(const uint8_t *enabledChannels, uint8_t nbEnabledChannels, uint8_t *channel);

            /** Gets the bitmask state containing the randomly used 125K channels
             * @return bitmask of the random channel distribution state - a '1' bit indicates the channel has
             *         not been used for randomization, a '0' indicates the channel has been used for randomization.
             */
            uint64_t ChannelState125K() const;

            /** Gets the bitmask state containing the randomly used 500K channels
             * @return bitmask of the random channel distribution state - a '1' bit indicates the channel has
             *         not been used for randomization, a '0' indicates the channel has been used for randomization.
             */

            uint32_t ChannelState500K() const;

            /** Sets the bitmask state caontaing the randomly used 125K channels
             * @param bitmask of the random channel distribution state - a '1' bit indicates the channel has
             *         not been used for randomization, a '0' indicates the channel has been used for randomization.
             */
            void ChannelState125K(uint64_t mask);

            /** Sets the bitmask state caontaing the randomly used 500K channels
             * @param bitmask of the random channel distribution state - a '1' bit indicates the channel has
             *         not been used for randomization, a '0' indicates the channel has been used for randomization.
             */
            void ChannelState500K(uint32_t mask);

            /** Marks all 8 channels for a subband to unused. This helper method is called
             *  typically whenever all the channels for a subband are pulled from a pool by NextChannel()
             *  to allow pulling another round of random values
             *
             *  @param subband subband to mark unused
             */
            void MarkAllSubbandChannelsUnused(uint8_t subband);

        private:

            /** Takes an array of enabled channels and stores the enabled channels as a bitmask grouped by
             *  their corresponding subbands. Channels not in the enabled list will be marked as disabled.
             *  Only enabled channels will be used in the pool for randomization.
             *
             *  @param enabledChannels list of enabled channels possible to be used for randomization
             *  @param nbEnabledChannels number of enabled channels in the list
             *  @return true if all enabledChannels are valid, else false
             */
            bool SetEnabledChannels(const uint8_t *enabledChannels, uint8_t nbEnabledChannels);

            /** Counts the number of channels that are enabled and have not yet been randomly picked by NextChannel().
             *  @return Number of enabled and unpicked channels
             */
            uint8_t CountUnusedChannels() const;

            /** Marks all 8 channels for a subband to unused. This helper method is called
             *  typically whenever all the channels for a subband are pulled from a pool by NextChannel()
             *  to allow pulling another round of random values
             *
             *  @param subband subband to mark unused
             */
            bool AllSubbandChannelsUsed(uint8_t subband) const;


            /** Walks through the bitmask array and pulls the nth (index) unused and enabled channel.
             *  When called, this method will set the unusedChannel bit to a '0' to indicate the value
             *  has been pulled to retain uniform randomization.
             *
             *  @param index number of active channels to pull from
             *  @param channel updated with the channel pulled, only valid when method returns true
             *  @return true if the channel could be pulled, else false
             */
            bool TakeActiveBit(uint8_t index, uint8_t *channel);


#if CHANNEL_PLAN == CP_CN470
            static const uint8_t NUM_125K_SUBBANDS = 8;
            static const uint8_t NUM_500K_SUBBANDS = 4;
#else
            static const uint8_t NUM_125K_SUBBANDS = 8;
            static const uint8_t NUM_500K_SUBBANDS = 1;
#endif

            static const uint8_t NUM_SUBBANDS = NUM_125K_SUBBANDS + NUM_500K_SUBBANDS;

            static const uint8_t CHANNELS_PER_SUBBAND = 8;

            static const uint8_t NUM_CHANNELS = (NUM_SUBBANDS * CHANNELS_PER_SUBBAND);

            static const uint8_t ALL_SUBBAND_CHANNELS_UNUSED = 0xFF;

            static const uint8_t SUBBAND_125K_INDEX = 0;

            static const uint8_t SUBBAND_500K_INDEX = 8;

            /** bitmask array for both 125K and 500K channels where a '1' bit indicates the channel
             *  has not yet been used for randomization and a '0' bit inidcates a channel has been
             *  used for randomization
             */
            uint8_t _unusedChannels[NUM_SUBBANDS] = {0};

            /** bitmask array for all 125K ands 500K channels to consider when pulling from randomization.
             */
            uint8_t _enabledChannels[NUM_SUBBANDS] = {0};
    };
}


