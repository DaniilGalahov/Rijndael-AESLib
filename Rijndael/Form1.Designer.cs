namespace Rijndael
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxSourceFilePath = new System.Windows.Forms.TextBox();
            this.buttonSelectSourceFile = new System.Windows.Forms.Button();
            this.openSourceFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.buttonSelectDestinationFile = new System.Windows.Forms.Button();
            this.textBoxDestinationFilePath = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.saveDestinationFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxEncryptionStandard = new System.Windows.Forms.ComboBox();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.buttonEncrypt = new System.Windows.Forms.Button();
            this.buttonDecrypt = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.linkLabelHelp = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Source file:";
            // 
            // textBoxSourceFilePath
            // 
            this.textBoxSourceFilePath.Location = new System.Drawing.Point(15, 26);
            this.textBoxSourceFilePath.Name = "textBoxSourceFilePath";
            this.textBoxSourceFilePath.Size = new System.Drawing.Size(375, 20);
            this.textBoxSourceFilePath.TabIndex = 1;
            // 
            // buttonSelectSourceFile
            // 
            this.buttonSelectSourceFile.Location = new System.Drawing.Point(396, 25);
            this.buttonSelectSourceFile.Name = "buttonSelectSourceFile";
            this.buttonSelectSourceFile.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectSourceFile.TabIndex = 2;
            this.buttonSelectSourceFile.Text = "Browse...";
            this.buttonSelectSourceFile.UseVisualStyleBackColor = true;
            this.buttonSelectSourceFile.Click += new System.EventHandler(this.buttonSelectSourceFile_Click);
            // 
            // openSourceFileDialog
            // 
            this.openSourceFileDialog.Title = "Choose source file";
            // 
            // buttonSelectDestinationFile
            // 
            this.buttonSelectDestinationFile.Location = new System.Drawing.Point(396, 65);
            this.buttonSelectDestinationFile.Name = "buttonSelectDestinationFile";
            this.buttonSelectDestinationFile.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectDestinationFile.TabIndex = 5;
            this.buttonSelectDestinationFile.Text = "Browse...";
            this.buttonSelectDestinationFile.UseVisualStyleBackColor = true;
            this.buttonSelectDestinationFile.Click += new System.EventHandler(this.buttonSelectDestinationFile_Click);
            // 
            // textBoxDestinationFilePath
            // 
            this.textBoxDestinationFilePath.Location = new System.Drawing.Point(15, 66);
            this.textBoxDestinationFilePath.Name = "textBoxDestinationFilePath";
            this.textBoxDestinationFilePath.Size = new System.Drawing.Size(375, 20);
            this.textBoxDestinationFilePath.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Destination file:";
            // 
            // saveDestinationFileDialog
            // 
            this.saveDestinationFileDialog.FileName = "output.bin";
            this.saveDestinationFileDialog.Title = "Choose destination file";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Location = new System.Drawing.Point(15, 106);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.Size = new System.Drawing.Size(325, 20);
            this.textBoxPassword.TabIndex = 7;
            this.textBoxPassword.UseSystemPasswordChar = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Password:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(348, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(75, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "AES standard:";
            // 
            // comboBoxEncryptionStandard
            // 
            this.comboBoxEncryptionStandard.FormattingEnabled = true;
            this.comboBoxEncryptionStandard.Items.AddRange(new object[] {
            "AES-128",
            "AES-192",
            "AES-256"});
            this.comboBoxEncryptionStandard.Location = new System.Drawing.Point(351, 105);
            this.comboBoxEncryptionStandard.Name = "comboBoxEncryptionStandard";
            this.comboBoxEncryptionStandard.Size = new System.Drawing.Size(121, 21);
            this.comboBoxEncryptionStandard.TabIndex = 10;
            this.comboBoxEncryptionStandard.Text = "AES-128";
            // 
            // buttonEncrypt
            // 
            this.buttonEncrypt.Location = new System.Drawing.Point(145, 140);
            this.buttonEncrypt.Name = "buttonEncrypt";
            this.buttonEncrypt.Size = new System.Drawing.Size(80, 23);
            this.buttonEncrypt.TabIndex = 11;
            this.buttonEncrypt.Text = "Encrypt";
            this.buttonEncrypt.UseVisualStyleBackColor = true;
            this.buttonEncrypt.Click += new System.EventHandler(this.buttonEncrypt_Click);
            // 
            // buttonDecrypt
            // 
            this.buttonDecrypt.Location = new System.Drawing.Point(275, 140);
            this.buttonDecrypt.Name = "buttonDecrypt";
            this.buttonDecrypt.Size = new System.Drawing.Size(80, 23);
            this.buttonDecrypt.TabIndex = 12;
            this.buttonDecrypt.Text = "Decrypt";
            this.buttonDecrypt.UseVisualStyleBackColor = true;
            this.buttonDecrypt.Click += new System.EventHandler(this.buttonDecrypt_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 176);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Status:";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(61, 176);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(38, 13);
            this.labelStatus.TabIndex = 14;
            this.labelStatus.Text = "Ready";
            // 
            // linkLabelHelp
            // 
            this.linkLabelHelp.AutoSize = true;
            this.linkLabelHelp.Location = new System.Drawing.Point(443, 176);
            this.linkLabelHelp.Name = "linkLabelHelp";
            this.linkLabelHelp.Size = new System.Drawing.Size(29, 13);
            this.linkLabelHelp.TabIndex = 15;
            this.linkLabelHelp.TabStop = true;
            this.linkLabelHelp.Text = "Help";
            this.linkLabelHelp.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelHelp_LinkClicked);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 201);
            this.Controls.Add(this.linkLabelHelp);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.buttonDecrypt);
            this.Controls.Add(this.buttonEncrypt);
            this.Controls.Add(this.comboBoxEncryptionStandard);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonSelectDestinationFile);
            this.Controls.Add(this.textBoxDestinationFilePath);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonSelectSourceFile);
            this.Controls.Add(this.textBoxSourceFilePath);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Rijndael AES cipher system";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxSourceFilePath;
        private System.Windows.Forms.Button buttonSelectSourceFile;
        private System.Windows.Forms.OpenFileDialog openSourceFileDialog;
        private System.Windows.Forms.Button buttonSelectDestinationFile;
        private System.Windows.Forms.TextBox textBoxDestinationFilePath;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.SaveFileDialog saveDestinationFileDialog;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxEncryptionStandard;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Button buttonEncrypt;
        private System.Windows.Forms.Button buttonDecrypt;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.LinkLabel linkLabelHelp;
    }
}

