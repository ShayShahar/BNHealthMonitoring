﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Caliburn.Micro;

namespace BNHealthMonitoring.UI.Model
{
    public class Link : PropertyChangedBase
    {
        public double Probability{ get; set; }
        public string DestenationName { get; set; }
        public int State { get; set; }
    }
}