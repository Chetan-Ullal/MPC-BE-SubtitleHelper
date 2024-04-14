# MPC-BE-SubtitleHelper

Provides a DirectShow filter called MPCSubtitleHelper that allows DirectShow compatible players to use MPC-VR and XYSubtitle filters and display subtitles without losing HDR info.

To do this, the player must also build the DirectShow graph with a video decoder filter that passes along the HDR info to the video renderer. Currently, LAVVideoDecoder and MPCVideoDecoder support this.

Steps:
1. Add MPC-VR, XYSubFilter, LAVVideoDecoder or MPCVideoDecoder and any other required filters to the DirectShow graph.
2. Add MPCSubtitleHelper filter to the graph.
3. Acquire the ISubtitleHelper interface from the MPCSubtitleHelper filter.
4. Call ISubtitleHelper::Connect() passing in the player's video window handle.
5. Connect the rest of the graph.
6. If the player uses IVideoWindow and/or IBasicVideo interfaces to send positioning information to the renderer, then it must also call ISubtitleHelper::SetPositionFromRenderer() to position the subtitles. If this is not done, the subtitle will not be visible.
7. The filter also exposes MPC-VR's IAllocatorPresenter interface, so it can be used for more advanced placement/configuration of the subtitles.
