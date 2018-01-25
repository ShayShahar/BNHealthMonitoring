NDSummary.OnToolTipsLoaded("File2:BL/CommunicationHandler.h",{988:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype988\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">CommunicationHandler</div></div></div><div class=\"TTSummary\">A communication handler class which manages the application\'s sockets.&nbsp; In order to get an instance of CommunicationHandler you should call the &quot;get_instance&quot; method.&nbsp; Note that this class implements the singleton pattern, which restricts the instantiation of the class to one object.</div></div>",989:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype989\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static bool</span> s_initialized</div></div>",990:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype990\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> CommunicationHandler* s_instance</div></div>",870:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype870\" class=\"NDPrototype NoParameterForm\">zmq::context_t* m_context</div></div>",871:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype871\" class=\"NDPrototype NoParameterForm\">zmq::socket_t* m_socket</div></div>",864:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype864\" class=\"NDPrototype NoParameterForm\">CommunicationHandler()</div><div class=\"TTSummary\">Prevents a default instance of the CommunicationHandler class from being created.</div></div>",866:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype866\" class=\"NDPrototype NoParameterForm\">~CommunicationHandler()</div><div class=\"TTSummary\">Finalizes an instance of the CommunicationHandler</div></div>",867:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype867\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> CommunicationHandler* get_instance()</div><div class=\"TTSummary\">returns the instance of CommunicationHandler</div></div>",874:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype874\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> init() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Initializes the communication handler.</div></div>",875:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype875\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> close() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Close the sockets</div></div>",873:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype873\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> send(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">HealthMonitoringMessages::</td><td class=\"PType\">DataUpdateMsg&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">p_msg</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Publish data message to subscribers.</div></div>"});