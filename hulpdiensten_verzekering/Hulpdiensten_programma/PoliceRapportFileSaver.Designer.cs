namespace Hulpdiensten_programma
{
    partial class PoliceRapportFileSaver
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.datetimePolTime = new System.Windows.Forms.DateTimePicker();
            this.label6 = new System.Windows.Forms.Label();
            this.txtPolLocX = new System.Windows.Forms.TextBox();
            this.datetimePolDate = new System.Windows.Forms.DateTimePicker();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txtPolLocY = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtPolTypeCrash = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtPolVicId = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtPolRapNumber = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.datetimePolTime);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.txtPolLocX);
            this.groupBox1.Controls.Add(this.datetimePolDate);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.txtPolLocY);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.txtPolTypeCrash);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtPolVicId);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtPolRapNumber);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(585, 261);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            // 
            // datetimePolTime
            // 
            this.datetimePolTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.datetimePolTime.Location = new System.Drawing.Point(446, 41);
            this.datetimePolTime.Name = "datetimePolTime";
            this.datetimePolTime.Size = new System.Drawing.Size(126, 22);
            this.datetimePolTime.TabIndex = 13;
            this.datetimePolTime.Value = new System.DateTime(2016, 12, 25, 0, 0, 0, 0);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(208, 165);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(108, 20);
            this.label6.TabIndex = 11;
            this.label6.Text = "X coordinate:";
            // 
            // txtPolLocX
            // 
            this.txtPolLocX.Location = new System.Drawing.Point(208, 188);
            this.txtPolLocX.Name = "txtPolLocX";
            this.txtPolLocX.Size = new System.Drawing.Size(131, 22);
            this.txtPolLocX.TabIndex = 12;
            // 
            // datetimePolDate
            // 
            this.datetimePolDate.Location = new System.Drawing.Point(208, 41);
            this.datetimePolDate.Name = "datetimePolDate";
            this.datetimePolDate.Size = new System.Drawing.Size(232, 22);
            this.datetimePolDate.TabIndex = 10;
            this.datetimePolDate.Value = new System.DateTime(2016, 12, 25, 0, 0, 0, 0);
            this.datetimePolDate.ValueChanged += new System.EventHandler(this.datetimePolDate_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(204, 18);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 20);
            this.label5.TabIndex = 9;
            this.label5.Text = "Date:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(208, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(107, 20);
            this.label4.TabIndex = 7;
            this.label4.Text = "Y coordinate:";
            // 
            // txtPolLocY
            // 
            this.txtPolLocY.Location = new System.Drawing.Point(208, 112);
            this.txtPolLocY.Name = "txtPolLocY";
            this.txtPolLocY.Size = new System.Drawing.Size(131, 22);
            this.txtPolLocY.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 165);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(116, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "Type of crash:";
            // 
            // txtPolTypeCrash
            // 
            this.txtPolTypeCrash.Location = new System.Drawing.Point(6, 188);
            this.txtPolTypeCrash.Name = "txtPolTypeCrash";
            this.txtPolTypeCrash.Size = new System.Drawing.Size(114, 22);
            this.txtPolTypeCrash.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 89);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "Victim ID:";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // txtPolVicId
            // 
            this.txtPolVicId.Location = new System.Drawing.Point(6, 112);
            this.txtPolVicId.Name = "txtPolVicId";
            this.txtPolVicId.Size = new System.Drawing.Size(114, 22);
            this.txtPolVicId.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(114, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Index number:";
            // 
            // txtPolRapNumber
            // 
            this.txtPolRapNumber.Location = new System.Drawing.Point(6, 41);
            this.txtPolRapNumber.Name = "txtPolRapNumber";
            this.txtPolRapNumber.Size = new System.Drawing.Size(114, 22);
            this.txtPolRapNumber.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 216);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(171, 34);
            this.button1.TabIndex = 1;
            this.button1.Text = "Save police rapport";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // PoliceRapportFileSaver
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(608, 285);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "PoliceRapportFileSaver";
            this.Text = "PoliceRapportFileSaver";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtPolRapNumber;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtPolVicId;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtPolTypeCrash;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtPolLocY;
        private System.Windows.Forms.DateTimePicker datetimePolDate;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtPolLocX;
        private System.Windows.Forms.DateTimePicker datetimePolTime;
    }
}