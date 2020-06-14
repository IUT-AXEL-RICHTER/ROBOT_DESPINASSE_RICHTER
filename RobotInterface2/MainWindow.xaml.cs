using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RobotInterface2
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public int count = 0;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ButtonEnvoyer_Click(object sender, RoutedEventArgs e)
        {

            if (count % 2 == 0)
            {
                ButtonEnvoyer.Background = Brushes.RoyalBlue;
            }
            else
            {
                ButtonEnvoyer.Background = Brushes.Beige;
            }
            count++;
            envoi();

        }

        private void Emission_KeyUp(object sender, KeyEventArgs e)
        {

            if (e.Key == Key.Enter)
            {
                envoi();
            }
        }

        private void envoi()
        {
            TextBoxReception.Text += TextBoxEmission.Text;
            TextBoxEmission.Text = "";
        }
        byte CalculateChecksum(int msgfunction, int msgPayLoadLenght, byte [] msgPayload)
        {
            byte checksum = 0;
            checksum ^= 0XFE;
            checksum ^= (byte)(msgfunction >> 8);
            checksum ^= (byte)(msgfunction >> 0);
            checksum ^= (byte)(msgPayLoadLenght >> 8);
            checksum ^= (byte)(msgPayLoadLenght >> 0);
            for(int i=0;i<msgPayLoadLenght;i++)
            {
                checksum ^= msgPayload[i];

            }
            return checksum;
        }
        void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, byte[] msgPayload)
        {

        }

        private void TextBoxEmission_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
        
