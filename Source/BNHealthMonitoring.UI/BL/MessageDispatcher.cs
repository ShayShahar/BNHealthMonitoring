using System.Text;
using HealthMonitoringMessages;
using NetMQ;
using NetMQ.Sockets;

namespace BNHealthMonitoring.UI.BL
{
    public class MessageDispatcher
    {
        private readonly SubscriberSocket m_socket;
        private readonly NetMQContext m_context;
        private readonly Poller m_poller;
        private static MessageDispatcher s_messageDispatcher;
        private readonly DataState m_dataState;

        private MessageDispatcher()
        {
            m_dataState = DataState.GetInstance();
            m_context = NetMQContext.Create();
            m_socket = m_context.CreateSubscriberSocket();

            m_poller = new Poller(m_socket);
            m_socket.ReceiveReady += onMessageReceived;
            m_poller.PollTillCancelledNonBlocking();

            m_socket.Connect("tcp://127.0.0.1:49993");
            m_socket.Subscribe("", Encoding.ASCII);
        }

        private void onMessageReceived(object p_sender, NetMQSocketEventArgs p_e)
        {
            var msg = DataUpdateMsg.ParseFrom(p_e.Socket.ReceiveFrameBytes());

            switch (msg.Opcode)
            {
                case OpCode.Components:
                    m_dataState.SetComponents(msg.Components);
                    break;
                case OpCode.SatLocation:
                    m_dataState.UpdateLocation(msg.Location);
                    break;
                case OpCode.Result:
                    m_dataState.UpdateAlgorithmOutput(msg.Result);
                    break;
            }
        }

        public static MessageDispatcher GetInsatnce()
        {
            if (s_messageDispatcher == null)
                s_messageDispatcher = new MessageDispatcher();

            return s_messageDispatcher;
        }

        public void Close()
        {
            m_poller.Cancel();
            m_socket.Disconnect("tcp://127.0.0.1:49993");
        }
    }
}