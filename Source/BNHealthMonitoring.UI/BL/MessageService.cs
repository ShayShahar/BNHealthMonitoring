using System;
using System.Text;
using HealthMonitoringMessages;
using NetMQ;
using NetMQ.Sockets;

namespace BNHealthMonitoring.UI.BL
{
    public class MessageService
    {
        private readonly SubscriberSocket m_socket;
        // private readonly RequestSocket m_requestSocket;
        private readonly NetMQContext m_context;
        private readonly Poller m_poller;
        private static MessageService s_messageService;
        private DataState m_dataState;

        private MessageService()
        {
            m_dataState = DataState.GetInstance();
            m_context = NetMQContext.Create();
            m_socket = m_context.CreateSubscriberSocket();
            //    m_requestSocket = m_context.CreateRequestSocket();

            m_poller = new Poller(m_socket);
            m_socket.ReceiveReady += onMessageReceived;
            m_poller.PollTillCancelledNonBlocking();

            // m_responsSocket.Bind("tcp://127.0.0.1:49993");
            m_socket.Connect("tcp://127.0.0.1:49993");
            m_socket.Subscribe("", Encoding.ASCII);
        }

        private void onMessageReceived(object p_sender, NetMQSocketEventArgs p_e)
        {
            var msg = DataReplyMsg.ParseFrom(p_e.Socket.ReceiveFrameBytes());

            switch (msg.Opcode)
            {
                case OpCode.Components:
                    m_dataState.SetComponents(msg.Components);
                    break;
            }



        }

        public static MessageService GetInsatnce()
        {
            if (s_messageService == null)
                s_messageService = new MessageService();

            return s_messageService;
        }

        public void RequestComponents()
        {
            //var msg = new DataRequestMsg.Builder();
            //msg.Opcode = OpCode.Components;

            //m_requestSocket.SendFrame(msg.Build().ToByteArray());

            //byte[] reply;
            //if (!m_requestSocket.TryReceiveFrameBytes(TimeSpan.FromMilliseconds(2000), out reply))
            //    return;

            //m_dataState.SetComponents(DataReplyMsg.ParseFrom(reply).Components);
        }

        public void Close()
        {


        }

    }
}