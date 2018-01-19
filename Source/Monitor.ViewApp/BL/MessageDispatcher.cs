﻿using System;
using System.Text;
using HealthMonitoringMessages;
using NetMQ;
using NetMQ.Sockets;

namespace Monitor.ViewApp.BL
{
    /// <summary>
    ///     MessageDispatcher class manage and handle the TCP/IP communication.
    ///     In order to get an instance of MessageDispatcher you should call the "GetInstacne" method.
    ///     Note that this class implemented the singleton pattern, which restricts the instantiation of the class to one
    ///     object.
    ///     The class implements the IDisposable interface which means that the Dispose method must be called before exiting 
    ///     the application in order to gracefully close the sockets.
    /// </summary>
    public class MessageDispatcher : IDisposable
    {
        #region Static Fields

        private static MessageDispatcher s_messageDispatcher;

        #endregion

        #region Fields

        private readonly NetMQContext m_context;
        private readonly DataState m_dataState;
        private readonly Poller m_poller;
        private readonly SubscriberSocket m_socket;

        #endregion

        #region Constructors and Destructors

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

        #endregion

        #region Public Methods and Operators

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

        public void Dispose()
        {
            Close();
            s_messageDispatcher = null;
        }

        #endregion

        #region Methods

        private void onMessageReceived(object p_sender, NetMQSocketEventArgs p_e)
        {
            try
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
                    case OpCode.LRU:
                        m_dataState.UpdateLruResult(msg.Result);
                        break;
                }
            }
            catch (Exception e)
            {
                //ignore socket exceptions
            }
        }

        #endregion
    }
}