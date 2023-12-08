--
-- PostgreSQL database dump
--

-- Dumped from database version 17devel
-- Dumped by pg_dump version 17devel

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: nl_ai; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS nl_ai WITH SCHEMA public;


--
-- Name: EXTENSION nl_ai; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION nl_ai IS 'PostgreSQL extension for natural language';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: courses; Type: TABLE; Schema: public; Owner: yashwanththummala
--

CREATE TABLE public.courses (
    course_id integer NOT NULL,
    course_name character varying(100),
    course_description text
);


ALTER TABLE public.courses OWNER TO yashwanththummala;

--
-- Name: courses_course_id_seq; Type: SEQUENCE; Schema: public; Owner: yashwanththummala
--

CREATE SEQUENCE public.courses_course_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.courses_course_id_seq OWNER TO yashwanththummala;

--
-- Name: courses_course_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: yashwanththummala
--

ALTER SEQUENCE public.courses_course_id_seq OWNED BY public.courses.course_id;


--
-- Name: enrollments; Type: TABLE; Schema: public; Owner: yashwanththummala
--

CREATE TABLE public.enrollments (
    enrollment_id integer NOT NULL,
    student_id integer,
    course_id integer,
    enrollment_date date,
    grade character varying(2)
);


ALTER TABLE public.enrollments OWNER TO yashwanththummala;

--
-- Name: enrollments_enrollment_id_seq; Type: SEQUENCE; Schema: public; Owner: yashwanththummala
--

CREATE SEQUENCE public.enrollments_enrollment_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.enrollments_enrollment_id_seq OWNER TO yashwanththummala;

--
-- Name: enrollments_enrollment_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: yashwanththummala
--

ALTER SEQUENCE public.enrollments_enrollment_id_seq OWNED BY public.enrollments.enrollment_id;


--
-- Name: instructors; Type: TABLE; Schema: public; Owner: yashwanththummala
--

CREATE TABLE public.instructors (
    instructor_id integer NOT NULL,
    name character varying(100),
    email character varying(100),
    specialization character varying(100)
);


ALTER TABLE public.instructors OWNER TO yashwanththummala;

--
-- Name: instructors_instructor_id_seq; Type: SEQUENCE; Schema: public; Owner: yashwanththummala
--

CREATE SEQUENCE public.instructors_instructor_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.instructors_instructor_id_seq OWNER TO yashwanththummala;

--
-- Name: instructors_instructor_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: yashwanththummala
--

ALTER SEQUENCE public.instructors_instructor_id_seq OWNED BY public.instructors.instructor_id;


--
-- Name: students; Type: TABLE; Schema: public; Owner: yashwanththummala
--

CREATE TABLE public.students (
    student_id integer NOT NULL,
    name character varying(100),
    email character varying(100),
    date_of_birth date
);


ALTER TABLE public.students OWNER TO yashwanththummala;

--
-- Name: students_student_id_seq; Type: SEQUENCE; Schema: public; Owner: yashwanththummala
--

CREATE SEQUENCE public.students_student_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.students_student_id_seq OWNER TO yashwanththummala;

--
-- Name: students_student_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: yashwanththummala
--

ALTER SEQUENCE public.students_student_id_seq OWNED BY public.students.student_id;


--
-- Name: courses course_id; Type: DEFAULT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.courses ALTER COLUMN course_id SET DEFAULT nextval('public.courses_course_id_seq'::regclass);


--
-- Name: enrollments enrollment_id; Type: DEFAULT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.enrollments ALTER COLUMN enrollment_id SET DEFAULT nextval('public.enrollments_enrollment_id_seq'::regclass);


--
-- Name: instructors instructor_id; Type: DEFAULT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.instructors ALTER COLUMN instructor_id SET DEFAULT nextval('public.instructors_instructor_id_seq'::regclass);


--
-- Name: students student_id; Type: DEFAULT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.students ALTER COLUMN student_id SET DEFAULT nextval('public.students_student_id_seq'::regclass);


--
-- Data for Name: courses; Type: TABLE DATA; Schema: public; Owner: yashwanththummala
--

COPY public.courses (course_id, course_name, course_description) FROM stdin;
1	Mathematics 101	Introduction to Mathematics
2	Physics 101	Fundamentals of Physics
3	Chemistry 101	Basic Chemistry Principles
4	Biology 101	Introduction to Biology
5	English Literature 101	English Literature Fundamentals
6	World History 101	Overview of World History
7	Computer Science 101	Fundamentals of Computing
8	Art 101	Introduction to Art
9	Economics 101	Principles of Economics
10	Psychology 101	Introduction to Psychology
\.


--
-- Data for Name: enrollments; Type: TABLE DATA; Schema: public; Owner: yashwanththummala
--

COPY public.enrollments (enrollment_id, student_id, course_id, enrollment_date, grade) FROM stdin;
1	1	1	2023-09-01	A
2	2	2	2023-09-01	B
3	3	3	2023-09-01	A
4	4	4	2023-09-01	B
5	5	5	2023-09-01	C
6	6	6	2023-09-01	A
7	7	7	2023-09-01	B
8	8	8	2023-09-01	C
9	9	9	2023-09-01	A
10	10	10	2023-09-01	B
\.


--
-- Data for Name: instructors; Type: TABLE DATA; Schema: public; Owner: yashwanththummala
--

COPY public.instructors (instructor_id, name, email, specialization) FROM stdin;
1	Dr. Alice Johnson	alice.johnson@example.com	Mathematics
2	Dr. Bob Brown	bob.brown@example.com	Physics
3	Dr. Charles Davis	charles.davis@example.com	Chemistry
4	Dr. Diane Evans	diane.evans@example.com	Biology
5	Dr. Edward Wilson	edward.wilson@example.com	English Literature
6	Dr. Fiona Garcia	fiona.garcia@example.com	History
7	Dr. George Harris	george.harris@example.com	Computer Science
8	Dr. Helen Clark	helen.clark@example.com	Art
9	Dr. Ian Moore	ian.moore@example.com	Economics
10	Dr. Jessica Taylor	jessica.taylor@example.com	Psychology
12	Dr. Alice Johnson	alice.johnson1@example.com	Mathematics
13	Dr. Bob Brown	bob.brown1@example.com	Physics
14	Dr. Charles Davis	charles.davis1@example.com	Chemistry
15	Dr. Diane Evans	diane.evans1@example.com	Biology
16	Dr. Edward Wilson	edward.wilson1@example.com	English Literature
17	Dr. Fiona Garcia	fiona.garcia1@example.com	History
18	Dr. George Harris	george.harris1@example.com	Computer Science
19	Dr. Helen Clark	helen.clark1@example.com	Art
20	Dr. Ian Moore	ian.moore1@example.com	Economics
21	Dr. Jessica Taylor	jessica.taylor1@example.com	Psychology
\.


--
-- Data for Name: students; Type: TABLE DATA; Schema: public; Owner: yashwanththummala
--

COPY public.students (student_id, name, email, date_of_birth) FROM stdin;
1	John Doe	john.doe@example.com	2000-01-01
2	Jane Smith	jane.smith@example.com	1999-05-15
3	Emily Johnson	emily.johnson@example.com	2001-02-20
4	Michael Brown	michael.brown@example.com	1998-07-31
5	Chloe Davis	chloe.davis@example.com	2000-11-12
6	William Garcia	william.garcia@example.com	1999-03-22
7	Elizabeth Miller	elizabeth.miller@example.com	2000-08-09
8	Daniel Wilson	daniel.wilson@example.com	1998-12-15
9	Megan Anderson	megan.anderson@example.com	2001-04-18
10	Christopher Martinez	christopher.martinez@example.com	1997-09-05
\.


--
-- Name: courses_course_id_seq; Type: SEQUENCE SET; Schema: public; Owner: yashwanththummala
--

SELECT pg_catalog.setval('public.courses_course_id_seq', 10, true);


--
-- Name: enrollments_enrollment_id_seq; Type: SEQUENCE SET; Schema: public; Owner: yashwanththummala
--

SELECT pg_catalog.setval('public.enrollments_enrollment_id_seq', 10, true);


--
-- Name: instructors_instructor_id_seq; Type: SEQUENCE SET; Schema: public; Owner: yashwanththummala
--

SELECT pg_catalog.setval('public.instructors_instructor_id_seq', 21, true);


--
-- Name: students_student_id_seq; Type: SEQUENCE SET; Schema: public; Owner: yashwanththummala
--

SELECT pg_catalog.setval('public.students_student_id_seq', 10, true);


--
-- Name: courses courses_pkey; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.courses
    ADD CONSTRAINT courses_pkey PRIMARY KEY (course_id);


--
-- Name: enrollments enrollments_pkey; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.enrollments
    ADD CONSTRAINT enrollments_pkey PRIMARY KEY (enrollment_id);


--
-- Name: instructors instructors_email_key; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.instructors
    ADD CONSTRAINT instructors_email_key UNIQUE (email);


--
-- Name: instructors instructors_pkey; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.instructors
    ADD CONSTRAINT instructors_pkey PRIMARY KEY (instructor_id);


--
-- Name: students students_email_key; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.students
    ADD CONSTRAINT students_email_key UNIQUE (email);


--
-- Name: students students_pkey; Type: CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.students
    ADD CONSTRAINT students_pkey PRIMARY KEY (student_id);


--
-- Name: enrollments enrollments_course_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.enrollments
    ADD CONSTRAINT enrollments_course_id_fkey FOREIGN KEY (course_id) REFERENCES public.courses(course_id);


--
-- Name: enrollments enrollments_student_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: yashwanththummala
--

ALTER TABLE ONLY public.enrollments
    ADD CONSTRAINT enrollments_student_id_fkey FOREIGN KEY (student_id) REFERENCES public.students(student_id);


--
-- PostgreSQL database dump complete
--

